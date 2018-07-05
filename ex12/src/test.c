#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include "test.h"

int test_small()
{
	char *foo = (char *)halloc(1);
	assert( foo > (char*)0x0000000000000001);
	my_free(foo);
	foo = (char *) halloc(10000000000000000000u);
	assert(foo == NULL);
	my_free(foo);
  foo = (char *) halloc(0);
	assert(foo == NULL);
  my_free(foo);
	return 0;
}

int test_long()
{
	int **a = (int **)halloc(sizeof(int) * 10000);
	for (int i = 0; i < 1000; i++)
	{
		int *tmp = (int *)halloc(sizeof(int));
		*tmp = i;
		a[i] = tmp;
	}
	for (int i = 0; i < 1000; i++)
		my_free(a[i]);
 	my_free(a);
	return 0;
}

int main()
{
  test_small();
	test_long();
/*  void *req1, *req2, *req3, *req4, *req5, *req6;

  req1 = sbrk(0);
  printf("brk before halloces : %p\n", req1);
  printf("size: %lu, pointersize: %lu, int size: %lu\n", sizeof(struct block_meta), sizeof(void*), sizeof(int));
  char *ch1 = halloc(5 * sizeof(char));
  req4 = sbrk(0);
  printf("brk after 1 halloc: %p, aloocated: %d\n", req4, (req4 - req1));
  char *ch2 = halloc(5 * sizeof(char));
  req5 = sbrk(0);
  printf("brk after 1 halloc: %p, aloocated: %d\n", req5, (req5 - req4));
  char *ch3 = halloc(5 * sizeof(char));
  req6 = sbrk(0);
  printf("brk after 1 halloc: %p, aloocated: %d\n", req6, (req6 - req5));

  req2 = sbrk(0);
  printf("brk after halloces: %p, allocated: %d\n", req2, (req2 - req1));

  for (char i = 0; i < 5; i++) {
    ch1[i] = '0' + i;
    ch2[i] = '0' + i + 10;
    ch3[i] = '0' + i + 30;
  }
  for (char i = 0; i < 5; i++) {
    printf("1: %c 2: %c 3: %c\n", ch1[i], ch2[i], ch3[i]);
  }

  my_free(ch1);
  my_free(ch2);
  my_free(ch3);

  req3 = sbrk(0);
  printf("brk after my_frees : %p, freed: %d, delta: %d\n", req3, (req2 - req3), (req3 - req1));
*/	return 0;
}
