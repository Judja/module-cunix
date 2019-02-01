#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include "filler.h"
#include "vector.h"
#include "my_string.h"

pos_t init_strategy(req_t *core, filler_t *filler) {
  filler->strategy = &go_center;
  filler->l_most = 0;
  filler->t_most = 0;
  filler->r_most = core->map.w;
  filler->b_most = core->map.h;

  return go_center(core, filler);
}

pos_t hs(req_t *core, filler_t *filler) {
  pos_t pos;

  gen_p(filler->possibilities, core);

  if (filler->possibilities->size  < 3)
    filler->strategy = &painter;

  compute_score(filler->possibilities, core);
  pos = pick_hs(filler->possibilities);

  return pos;
}

pos_t painter(req_t *core, filler_t *filler) {
  pos_t pos;

  for(int i = 0; i < core->map.h; i++) {
    for(int j = 0; j < core->map.w; j++) {
      pos.x = j;
      pos.y = i;

      if(!check_free_space(&(core->map), &(core->elem), pos) && !check_connection(&(core->map), &(core->elem), pos, core->symbol))
        return pos;
    }
  }

  if (0) filler->strategy = &painter; // special for" unused parameter" warning

  pos.x = -10;
  pos.y = -10;

  return pos;
}

pos_t go_center(req_t *core, filler_t *filler) {
  pos_t center, pos;
  int dx, dy;
  center.x = core->map.w / 2;
  center.y = core->map.h / 2;

  gen_p(filler->possibilities, core);
  compute_dist(filler->possibilities, center);

  pos = pick_hs(filler->possibilities);

  dx = pos.x - center.x;
  dy = pos.y - center.y;

  if ((dx * dx + dy * dy) < 50)
    filler->strategy = &hs;

  return pos;
}

void compute_dist(vector_t *vector, pos_t point) {
  pos_t p;
  int dx, dy;

  for (int ind = 0; ind < vector->size; ind++) {
    p = vector->buffer[ind].pos;
    dx = p.x - point.x;
    dy = p.y - point.y;
    vector->buffer[ind].score = -1 * (dx * dx + dy * dy);
  }
}
