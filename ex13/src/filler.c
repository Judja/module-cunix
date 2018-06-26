#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include "my_string.h"

void create_filler(filler_t **filler) {
  *filler = malloc(sizeof(filler_t));
  (*filler)->current_stream = string_init();
  (*filler)->status = 0;
  (*filler)->find_enemy = 0;
}

void destroy_filler(filler_t **filler) {
  string_destroy((*filler)->current_stream);
  free(*filler);
  *filler = NULL;
}

void create_req(req_t **req) {
  *req = malloc(sizeof(req_t));
}

void destroy_req(req_t **req) {
  free(*req);
  *req = NULL;
}

int main() {
  filler_t *filler = NULL;
  log_init();

  create_filler(&filler);

  start_game(filler);

  destroy_filler(&filler);

  return 0;
}