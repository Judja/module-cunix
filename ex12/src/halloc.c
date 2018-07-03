#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

struct block_meta {
  size_t size;
  struct block_meta *next;
  struct block_meta *prev;
  int free;
};

#define META_SIZE sizeof(struct block_meta)
#define align4(x) (((((x) - 1) >> 2) << 2) + 4)

void *global_base = NULL;

struct block_meta *find_free_block(struct block_meta **last, size_t size) {
  struct block_meta *current;

  current = global_base;

  while (current && !(current->free && current->size >= size)) {
    *last = current;
    current = current->next;
  }

  return current;
}

struct block_meta *request_space(struct block_meta* last, size_t size) {
  struct block_meta *block;
  void *request;

  block = sbrk(0);
  request = sbrk(size + META_SIZE);

  if (request == (void*)(-1))
    return NULL; // sbrk failed.

  if (last)// NULL on first request.
    last->next = block;

  block->size = size;
  block->next = NULL;
  block->free = 0;
  block->prev = last;

  return block;
}

void split_block(struct block_meta *b, size_t s) {
  struct block_meta *new;

  new = (struct block_meta*)(b + META_SIZE + s);
  new->size = b->size - s - META_SIZE;
  new->next = b->next;
  new->prev = b;
  new->next->prev = new;
  new->free = 1;
  b->size = s;
  b->next = new;
}

void *halloc(size_t size) {
  struct block_meta *block, *last;

  if (size <= 0)
    return NULL;

  size = align4(size);

  if (!global_base) { // First call.
    block = request_space(NULL, size);
    if (!block)
      return NULL;

    block->prev = NULL;
    global_base = block;
  }
  else {
    last = global_base;
    block = find_free_block(&last, size);
    if (!block) { // Failed to find free block.
      block = request_space(last, size);
      if (!block)
        return NULL;
    }
    else {      // Found free block
      if ((block->size - size) >= (META_SIZE + 4))
        split_block(block, size);
      block->free = 0;
    }
  }

  return(block+1);
}

struct block_meta *get_block_ptr(void *ptr) {
  return (struct block_meta*)ptr - 1;
}

struct block_meta* merge_with_next(struct block_meta *ptr) {
  ptr->size = ptr->size + META_SIZE + ptr->next->size;
  ptr->next = ptr->next->next;

  if (ptr->next)
    ptr->next->prev = ptr;

  return ptr;
}

void free(void *ptr) {
  struct block_meta* block_ptr;

  if (!ptr)
    return;

  block_ptr = get_block_ptr(ptr);

  if (block_ptr->prev && block_ptr->prev->free)
    block_ptr = merge_with_next(block_ptr->prev);

  if (block_ptr->next && block_ptr->next->free)
    block_ptr = merge_with_next(block_ptr);

  block_ptr->free = 1;

  if (!block_ptr->next) {//releasing freed space to system
    if (!block_ptr->prev) //the only one elem in linked list
      global_base = NULL;

    else //last elem in linked list
      block_ptr->prev->next = NULL;

    brk(block_ptr);
  }
}
