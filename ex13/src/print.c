#include <stdio.h>
#include "filler.h"

void print_pos(pos_t pos) {
  my_log_f("POSITION: %d, %d\n", pos.x, pos.y);
  dprintf(1, "%i %i", pos.x, pos.y);
}
