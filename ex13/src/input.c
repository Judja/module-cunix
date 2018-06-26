#include <unistd.h>
 #include <stdio.h>
 #include <string.h>
 #include <fcntl.h>
 #include "my_string.h"

int set_nonblocking(int fd) {
  int flags;

  flags  = fcntl(fd, F_GETFL, 0);
  return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

void read_input(filler_t *filler){
  char str[BUF_SIZE];
  int res;

  while(1) {
    res = read(0, str, BUF_SIZE - 1);
    str[res] = '\0';
    string_append(filler->current_stream, str);
    if (strlen(str) < 63) break;
  }
}


