#ifndef TEST_H_
# define TEST_H_

#include <stddef.h>

struct block_meta {
  size_t size;
  void *ptr;
  struct block_meta *next;
  struct block_meta *prev;
  int my_free;
};

void *halloc (size_t size);

void my_free(void *ptr);

#endif
