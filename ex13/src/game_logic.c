#include <stdio.h>
#include <stdlib.h>
#include "../include/filler.h"

pos_t 		play(req_t *core, filler_t *filler)
{
  pos_t 	res;
  FILE 	*logger;
  int 	h;
  int 	w;
  int 	flag;

  flag = 1;
  h = core->map.h;
  w = core->map.w;

  logger = fopen("filler.log", "a");
  fprintf(logger, "Play\n");
  fprintf(logger, "core->map.h = %d, core->map.w = %d/n", core->map.h, core->map.w);
  fclose(logger);

  for(int i = h-1; i>=0; i--)
    for(int j = 0; j < w; j++)
    {
      logger = fopen("filler.log", "a");
      fprintf(logger, "Play circle\n");
      fclose(logger);
      
      res.x = j;
      res.y = i;

      pos_t temp;
      temp.x = res.x;
      temp.y = res.y;

      for(int m = 0; m < w; m++)
      if(core->map.array[h-1][m] == core->symbol)
      {
        res.x = -100;
        res.y = -100;
        flag = 0;
        break;
      }

      for(int m = 0; m < h; m++)
      if(core->map.array[m][0] == core->symbol)
      {
        res.x = -100;
        res.y = -100;
        flag = 0;
        break;
      }

      if(!check_free_space(&(core->map), &(core->elem), res) && !check_connection(&(core->map), &(core->elem), res, core->symbol))
      {
        logger = fopen("filler.log", "a");
        fprintf(logger, "RES POS = %d %d\n", res.x, res.y);
        fclose(logger);
        return res;
      }
      else
      {
        logger = fopen("filler.log", "a");
        fprintf(logger, "%d and %d don't fit\n", i, j);
        fclose(logger);
      }
    }

  if(flag == 0)
    for(int i = 0; i < h; i++)
      for(int j = w - 1; j >= 0; j--)
      {
        res.x = j;
        res.y = i;

        for(int m = 0; m < w; m++)
        if(core->map.array[0][m] == core->symbol)
        {
          res.x = -100;
          res.y = -100;
          flag = 2;
          break;
        }

        for(int m = 0; m < h; m++)
        if(core->map.array[m][w-1] == core->symbol)
        {
          res.x = -100;
          res.y = -100;
          flag = 2;
          break;
        }

        if(!check_free_space(&(core->map), &(core->elem), res) && !check_connection(&(core->map), &(core->elem), res, core->symbol))
        {
          logger = fopen("filler.log", "a");
          fprintf(logger, "RES POS = %d %d\n", res.x, res.y);
          fclose(logger);
          return res;
        }
      }

  if(flag == 2)
  {
    logger = fopen("filler.log", "a");
    fprintf(logger, "Flag 2 \n");
    fclose(logger);

    for(int i = 0; i < (w+h)/2; i++)
    {
      res.x = i;
      res.y = i;
      for(int m = 0; m < w/8 * 1; m++)
      if(core->map.array[0][m] == core->symbol)
      {
        res.x = -100;
        res.y = -100;
        break;
      }
      for(int m = 0; m < h/8 * 1; m++)
      if(core->map.array[m][0] == core->symbol)
      {
        res.x = -100;
        res.y = -100;
        flag = 4;
        break;
      }

      if(!check_free_space(&(core->map), &(core->elem), res) && !check_connection(&(core->map), &(core->elem), res, core->symbol))
      {
        logger = fopen("filler.log", "a");
        fprintf(logger, "RES POS = %d %d\n", res.x, res.y);
        fclose(logger);
        return res;
      }
    }
  }

  for(int j = w - 1; j >= 0; j--)
  for(int i = h - 1; i >= 0; i--)
  {
    res.x = j;
    res.y = i;

    if(!check_free_space(&(core->map), &(core->elem), res) && !check_connection(&(core->map), &(core->elem), res, core->symbol))
    {
      logger = fopen("filler.log", "a");
      fprintf(logger, "RES POS = %d %d\n", res.x, res.y);
      fclose(logger);
      return res;
    }
    else
    {
      logger = fopen("filler.log", "a");
      fprintf(logger, "%d and %d not mine point \n", i, j);
      fclose(logger);
    }
  }

  return res;
}
