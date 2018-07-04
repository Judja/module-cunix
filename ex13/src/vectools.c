#include <stdlib.h>
#include "vector.h"

void gen_p(vector_t *vector, req_t *core) {
  pos_t p;
  possib_t possib;

  possib.score = 0;
  vector_reset(vector);

  for (int i = 0; i <= core->map.h - core->elem.h; i++) {
    for (int j = 0; j <= core->map.w - core->elem.w; j++) {
      p.x = j;
      p.y = i;
      if (check_placable(&core->map, &core->elem, p, core->symbol)) {
        possib.pos = p;
        vector_push(vector, possib);
      }
    }
  }
}

void compute_score(vector_t *vector, req_t *core) {
  int r = 5;
  int l, t, sum;
  char ch;

  for (int ind = 0; ind < vector->size; ind++) {
    l = vector->buffer[ind].pos.x - r;
    t = vector->buffer[ind].pos.y - r;
    sum = 0;

    for (int i = 0; i < r * 2 + core->elem.h; i++) {
      for (int j = 0; j < r * 2 + core->elem.w; j++) {
        if ((j + l < 0 || j + l >= core->map.w) && (sum += 2))
          continue;
        if ((t + i < 0 || t + i >= core->map.h) && (sum += 2))
          continue;

        ch = core->map.array[t + i][j + l];

        if (ch == '.') sum += 1;
        else if (ch == core->symbol) sum += 0;
        else sum += 3;
      }
    }

    vector->buffer[ind].score = sum;
  }
}

pos_t pick_hs(vector_t *vector) {
  int hs;
  pos_t p;

  if (vector->size < 1) {
    p.x = -1;
    p.y = -1;
    return p;
  }

  hs = vector->buffer[0].score;
  p = vector->buffer[0].pos;

  for (int i = 1; i < vector->size; i++) {
    if (vector->buffer[i].score > hs) {
      hs = vector->buffer[i].score;
      p = vector->buffer[i].pos;
    }
  }

  return p;
}

pos_t pick_rand(vector_t *vector) {
  srand(7);

  return vector->buffer[rand() % vector->size].pos;
}

