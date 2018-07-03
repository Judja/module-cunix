#include <stdlib.h>
#include "vector.h"

vector_t* vector_create() {
  vector_t *ptr;

  ptr = malloc(sizeof(vector_t));
  ptr->limit = LIMIT;
  ptr->size = 0;
  ptr->buffer = malloc(ptr->limit * sizeof(possib_t));

  return ptr;
}

void vector_destroy(vector_t *vector) {
  free(vector->buffer);
  free(vector);
}

void vector_reset(vector_t *vector) {
  vector->size = 0;
}

void vector_push(vector_t *vector, possib_t possib) {
  vector->buffer[vector->size++] = possib;

  if (vector->size == vector->limit) {
    vector->limit = vector->limit << 1;
    vector->buffer = realloc(vector->buffer, vector->limit);
  }
}
