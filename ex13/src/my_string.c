#include "my_string.h"

#include <stdlib.h>
#include <string.h>

#include <stdio.h>

stream_t* string_init() {
  stream_t *new_str;

  new_str = malloc(sizeof(stream_t));

  new_str->size = 0;
  new_str->limit = BUF_SIZE;
  new_str->str = malloc(new_str->limit);
  new_str->str[0] = '\0';

  return new_str;
}

stream_t* string_create(char *str) {
  stream_t *new_str;

  new_str = string_init();

  string_append(new_str, str);

  return new_str;
}

void string_append(stream_t *ptr, char *str) {
  int len, len2;

  len = strlen(str);

  if (len == 0) return;
  len2 = ptr->size + 1 + len;

  if (len2 > ptr->limit) {
    do {
      ptr->limit = ptr->limit << 1;
    } while(len2 > ptr->limit);

    ptr->str = realloc(ptr->str, ptr->limit);
  }

  for (int i = 0; i <= len; i++)
    ptr->str[ptr->size + i] = str[i];

  ptr->size += len;
}

void string_destroy(stream_t *ptr) {
  free(ptr->str);
  free(ptr);
}

/*int main() {
  stream_t *str2, *str1;

  str2 = string_init();
  string_append(str2, "Halllo");

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
  string_append(str2, "tail");

  printf("%s\n", str2->str);
  printf("size: %d, len: %d, limit: %d\n", str2->size, (int)strlen(str2->str), str2->limit);

  str1 = string_create("tgggggggggggsgsgsgsggsgsggsgsgsggsggsgsgsgsgsgsggsgsgsgsgggsgsgsgsgsggsgsgsgsggsgsgsgsgsgsgsgsgsgsgsggsgsgsgsgsgsgsggsgsgsgsgsgsgsgsgsgsgsgsgsg`k");
  printf("%s\n", str1->str);
  printf("size: %d, len: %d, limit: %d\n", str1->size, (int)strlen(str1->str), str1->limit);

  string_destroy(str2);
  string_destroy(str1);

  return 0;
}*/
