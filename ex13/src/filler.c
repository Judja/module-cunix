#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include "filler.h"
#include "vector.h"
#include "my_string.h"

void create_filler(filler_t *filler) {
  filler->current_stream = NULL;
  filler->status = 0;
  filler->strategy = &init_strategy;
  filler->possibilities = vector_create();
  my_log_f("\nSIZE: %d\n", filler->possibilities->size);
}

void destroy_filler(filler_t *filler) {
  string_destroy(filler->current_stream);
  vector_destroy(filler->possibilities);
}

req_t *create_req() {
  req_t   *req;
  req = (req_t *)malloc(sizeof(req_t));

  return req;
}

void destroy_req(req_t *req) {
  elem_destroy(&req->map);
  elem_destroy(&req->elem);
  free(req);

  req = NULL;
}

elem_t elem_init(int width, int height) {
  elem_t   elem;

  elem.array = malloc(height * sizeof(char *));

  for(int i = 0; i < height; i++)
    elem.array[i] = malloc((width + 1) * sizeof(char));

  elem.h = height;
  elem.w = width;

  return elem;
}

elem_t elem_read(char *source, int pos, int w, int h) {
  elem_t elem = elem_init(w, h);

  for(int i = 0; i < elem.h; i++) {
    for(int j = 0; j < elem.w; j++) {
      elem.array[i][j] = source[pos];
      pos++;
    }
    elem.array[i][elem.w] = '\0';
    pos++;
  }

  return elem;
}

void elem_destroy(elem_t *elem) {
  for(int i = 0; i < elem->h; i++)
    free(elem->array[i]);

  free(elem->array);
  elem->array = NULL;
}

int set_nonblocking(int fd) {
  int flag;

  flag = fcntl(fd, F_GETFL, 0) | O_NONBLOCK;
  return fcntl(fd, F_SETFL, flag);
}

void fatal(char *msg) {
  int size = strlen(msg);

  if(msg) write(2, msg, size);

  exit(1);
}
