#include "filler.h"
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

#define LOG_MODE 0

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

void my_log_f(char* format, ...) {
  if (!LOG_MODE) return;
  va_list argptr;
  FILE *fd;

  fd = fopen("log", "a");

	va_start(argptr, format);
  vfprintf(fd, format, argptr);
  va_end(argptr);

  fclose(fd);
}

