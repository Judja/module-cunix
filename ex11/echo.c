#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  write(1, argv[1], strlen(argv[1]));
  return 0;
}