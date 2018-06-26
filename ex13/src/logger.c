#include "filler.h"
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define LOG_MODE 1

void log_init() {
  if(!LOG_MODE) return;
  int fd;

  fd = open("log", O_RDWR|O_CREAT|O_TRUNC);
  close(fd);
}

void my_log(char *str) {
  if (!LOG_MODE) return;
  int fd, len;
  char* ptr;

  fd = open("log", O_RDWR|O_CREAT|O_APPEND);

  len = strlen(str);

  ptr = str;

  while (len > 64) {
    write(fd, ptr, 64);
    ptr += 64;
    len -= 64;
  }

  write(fd, ptr, len);

  close(fd);
}

