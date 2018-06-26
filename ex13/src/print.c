#include <stdio.h>
#include <stdlib.h>
#include "../include/filler.h"

void 		print_pos(pos_t p)
{
	FILE 	*logger;

	dprintf(1, "%d %d", p.x, p.y);

	logger = fopen("filler.log" , "a");
	fprintf(logger, "Print pos: %d %d\n", p.x, p.y);
	fclose(logger);
}
