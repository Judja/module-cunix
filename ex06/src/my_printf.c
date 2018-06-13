#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

unsigned int my_strlen(char *str) {
  unsigned i;
  for(i = 0; *(str + i) != '\0'; i++);
  return i;
}

int my_atoi(const char *nptr) {
  int i = 0;
  char minus = 0;

  if (*nptr == '-') {
    nptr++;
    minus = 1;
  }
  while (*nptr != '\0') {
    if (*nptr >= '0' && *nptr <= '9') {
      i *= 10;
      i += *nptr - '0';
    }
    else {
      break;
    }
    nptr++;
  }

  return (minus)? i*=-1 : i;
}

char* my_itoa(int nmb) {
  char *ptr, *buf;
  buf = malloc(16 * sizeof(char));
  ptr = buf;
  int i = 1, n;

  if (nmb < 0) {
    nmb = -1 * nmb;
    *buf++ = '-';
  }

  n = nmb;

  while (n > 9) {
    n /= 10;
    i *= 10;
  }

  while (i > 0) {
    n = nmb / i;
    *buf++ = '0' + n;
    nmb -= i * n;
    i /= 10;
  }
  *buf = '\0';

  return ptr;
}

int my_printf(const char* format, ...) {
  extern long write(int, const char*, unsigned int);

  va_list arg_list;
  unsigned char symb;
  char *st, *padd_str, *str, *padd_str_init, *str_start_ptr;
  int padding;

  str = malloc(256 * sizeof(char));
  str_start_ptr = str;
  padd_str_init = malloc(16 * sizeof(char));
  va_start(arg_list, format);

  while(*format != '\0') {

    if(*format == '%') {
      padding = 0;
      symb = 0;
      padd_str = padd_str_init;

      format++;
      while(*format != ' ' && *format != '\0') {
        if(*format == '%'){
          *str++ = '%';
          format++;
          break;
        }
        if(*format == '0'){
          symb = '0';
          format++;
        }
        while(*format >= '0' && *format <= '9')
          *padd_str++ = *format++;

        *padd_str = '\0';
        padding = my_atoi(padd_str_init);
        if(*format == 's'){
          st = va_arg(arg_list, char *);
        }
        if(*format == 'd'){
          int i = va_arg(arg_list, int);
          st = my_itoa(i);
        }
        padding -= strlen(st);
        while(padding-- > 0) *str++ = (symb)?symb:' ';
        while(*st != '\0')
          *str++ = *st++;

        format++;
        break;
      }
      continue;
    }
    *str++ = *format++;
  }
  *str = '\0';

  write(1, str_start_ptr, strlen(str_start_ptr));
  va_end(arg_list);
  free(padd_str_init);
  free(str_start_ptr);
  return 0;
}