#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include "filler.h"
#include "vector.h"
#include "my_string.h"

pos_t init_strategy(req_t *core, filler_t *filler) {
  filler->strategy = &hs;
  filler->l_most = 0;
  filler->t_most = 0;
  filler->r_most = core->map.w;
  filler->b_most = core->map.h;

  return hs(core, filler);
}

pos_t hs(req_t *core, filler_t *filler) {
  pos_t res;
  res.x = -10;
  res.y = -10;

  gen_p(filler->possibilities, core, filler);
  res = pick_hs(filler, core);

  my_log_f("SIZE: %d, x: %d, y:, %d\n", filler->possibilities->size, res.x, res.y);

  return res;
}

pos_t randm(req_t *core, filler_t *filler) {
  pos_t pos;

  pos.x = -1;
  pos.y = -1;

  gen_p(filler->possibilities, core, filler);

  pos = pick_rand(filler->possibilities);

  return pos;
}


