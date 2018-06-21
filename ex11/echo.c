#include <string.h>

int main(int argc, char *argv[]) {
  write(1, argv[1], strlen(argv[1]));
  write(1, "hello", 5);
  return 0;
}