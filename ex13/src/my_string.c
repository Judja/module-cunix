#include "my_string.h"

#include <stdlib.h>
#include <string.h>

#include <stdio.h>

stream_t* string_init() {
  stream_t *new_str;

  new_str = malloc(sizeof(stream_t));

  new_str->size = 0;
  new_str->limit = 1;
  new_str->str = malloc(sizeof(char));
  new_str->str[0] = '\0';

  return new_str;
}

stream_t* string_create(char *str) {
  stream_t *new_str;
  int len;

  new_str = malloc(sizeof(stream_t));

  len = strlen(str) + 1;

  new_str->size = len - 1;
  new_str->limit = len;
  new_str->str = malloc(len * sizeof(char));
  strcpy(new_str->str, str);

  return new_str;
}

void string_append(stream_t *ptr, char *str) {
  int len;

  len = strlen(str);

  if (len == 0) return;

  ptr->str = realloc(ptr->str, (len + ptr->limit) * sizeof(char));

  ptr->limit += len;
  for (int i = 0; i <= len; i++)
    ptr->str[ptr->size + i] = str[i];

  ptr->size += len;
}

void string_destroy(stream_t *ptr) {
  free(ptr->str);
  free(ptr);
}

int main() {
  stream_t *str1, *str2;

  str1 = string_init();
  string_append(str1, "ttt");
  str2 = string_create("Halllo");

  string_append(str2, " there");
  printf("%s\n", str1->str);
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  string_append(str2, " there");
  printf("%s\n", str2->str);

  string_destroy(str1);
  string_destroy(str2);

  return 0;
}
