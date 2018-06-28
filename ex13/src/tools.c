#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include "filler.h"
#include "my_string.h"

void create_filler(filler_t *filler) {
  filler->current_stream = NULL;
  filler->status = 0;
  filler->strategy = &init_strategy;
}

void destroy_filler(filler_t *filler) {
  string_destroy(filler->current_stream);
}

req_t *create_req() {
  req_t   *req;
  req = (req_t *)malloc(sizeof(req_t));

  return req;
}

void destroy_req(req_t *req) {
  content_destroy(&req->map);
  content_destroy(&req->elem);
  free(req);

  req = NULL;
}

content_t content_init(int width, int height) {
  content_t   content;

  content.array = malloc(height * sizeof(char *));

  for(int i = 0; i < height; i++)
    content.array[i] = malloc((width + 1) * sizeof(char));

  content.h = height;
  content.w = width;

  return content;

}

content_t content_read(char *source, int pos, int w, int h) {
  content_t content = content_init(w, h);

  for(int i = 0; i < content.h; i++) {
    for(int j = 0; j < content.w; j++) {
      content.array[i][j] = source[pos];
      pos++;
    }
    content.array[i][content.w] = '\0';
    pos++;
  }

  return content;
}

void content_destroy(content_t *content) {
  for(int i = 0; i < content->h; i++)
    free(content->array[i]);

  free(content->array);
  content->array = NULL;
}

void printlog(const char *filename, const char *mode, const char *format, ...) {
  va_list arg;
  FILE *logger;

  logger = fopen(filename, mode);

  va_start(arg, format);
  vfprintf(logger, format, arg);
  va_end(arg);

  fclose(logger);
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
