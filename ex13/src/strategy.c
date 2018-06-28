#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include "filler.h"
#include "my_string.h"

pos_t init_strategy(req_t *core, filler_t *filler) {
  filler->strategy = &tupik;
  return tupik(core, filler);
}

pos_t tupik(req_t *core, filler_t *filler) {
  pos_t res;
  FILE *logger;
  res.x = -10;
  res.y = -10;

  logger = fopen("filler.log", "a");
  fprintf(logger, "Play\n");
  fprintf(logger, "core->map.h = %d, core->map.w = %d", core->map.h, core->map.w);
  fclose(logger);

  for(int i = 0; i < core->map.h; i++)
    for(int j = 0; j < core->map.w; j++) {
      logger = fopen("filler.log", "a");
      fprintf(logger, "Play circle\n");
      fclose(logger);

      res.x = j;
      res.y = i;

      if(!check_free_space(&(core->map), &(core->elem), res) && !check_connection(&(core->map), &(core->elem), res, core->symbol)) {
        logger = fopen("filler.log", "a");
        fprintf(logger, "RES POS = %d %d\n", res.x, res.y);
        fclose(logger);

        return res;
      }
    }

  if (0) filler->strategy = &tupik; //"Fuck Off" sign for "unused parameter" warnings
  res.x = -10;
  res.y = -10;

  return res;
}
