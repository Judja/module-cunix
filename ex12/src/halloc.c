#include "test.h"
#include <stdlib.h>

void *halloc(size_t size) {
	void *ptr;
	
	if (size <= 0)
	  return NULL;
	
	ptr = malloc(size);
	
	if (ptr == (void*) -1)
	  return NULL;
	  
	return ptr;
}
