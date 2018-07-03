#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

struct block_meta {
  size_t size;
  struct block_meta *next;
  int free;
};

#define META_SIZE sizeof(struct block_meta)
#define align4(x) (((((x) - 1) >> 2) << 2) + 4)

void *global_base = NULL;

struct block_meta *find_free_block(struct block_meta **last, size_t size) {
  struct block_meta *current = global_base;
  while (current && !(current->free && current->size >= size)) {
    *last = current;
    current = current->next;
  }
  return current;
}

struct block_meta *request_space(struct block_meta* last, size_t size) {
  struct block_meta *block;
  block = sbrk(0);
  void *request = sbrk(size + META_SIZE);
  if (request == (void*)(-1)) {
    return NULL; // sbrk failed.
  }

  if (last) { // NULL on first request.
    last->next = block;
  }
  block->size = size;
  block->next = NULL;
  block->free = 0;
  return block;
}

void split_block(struct block_meta *b, size_t s) {
  struct block_meta *new;
  new = (struct block_meta*)(b + META_SIZE + s);
  new->size = b->size - s - META_SIZE;
  new->next = b->next;
  new->free = 1;
  b->size = s;
  b->next = new;
}
void *halloc(size_t size) {
  struct block_meta *block;

  if (size <= 0) {
    return NULL;
  }

  size = align4(size);

  if (!global_base) { // First call.
    block = request_space(NULL, size);
    if (!block) {
      return NULL;
    }
    global_base = block;
  } else {
    struct block_meta *last = global_base;
    block = find_free_block(&last, size);
    if (!block) { // Failed to find free block.
      block = request_space(last, size);
      if (!block) {
        return NULL;
      }
    } else {      // Found free block
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

int list_len() {
  struct block_meta *ptr = global_base;
  int res = 0;

  while(ptr) {
    res++;
    ptr = ptr->next;
  }

  return res;
}

void merge_free(struct block_meta *base) {
  struct block_meta *prev, *cur;
  if(!base) return;
  if(!base->next) return;
  prev = base;
  cur = base->next;
  while(cur != NULL) {
    if(prev->free && cur->free) {
      prev->next = cur->next;
      prev->size += (cur->size + META_SIZE);
      cur = cur->next;
      continue;
    }
    prev = prev->next;
    cur = cur->next;
  }
}

void free(void *ptr) {
  if (!ptr) {
    return;
  }

  merge_free(global_base);
  struct block_meta* block_ptr = get_block_ptr(ptr);
  block_ptr->free = 1;
}
