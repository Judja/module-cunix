#include <stdio.h>
#include "filler.h"
#include "my_string.h"

int main() {
  filler_t  filler;

  log_init();
  create_filler(&filler);
  start_game(&filler);

  return 0;
}
