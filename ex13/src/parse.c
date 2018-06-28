#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "filler.h"

int find_size(char *dist, char *source, int start) {
  int       end;

  end = start;
  while(source[end] != '\n')
    end++;

  strncpy(dist, source + start, end - start);
  dist[end - start] = '\0';

  return end - 1;
}

pos_t parse_size(char *answer) {
  int i, size;
  char *left, *right;
  pos_t pos;

  size = strlen(answer);
  left = malloc(size);
  right = malloc(size);

  memset(left, '\0', size);
  memset(right, '\0', size);

  for(i = 0; i < size && answer[i] != ' '; i++);

  left = strncpy(left, answer, i);
  right = strcpy(right, answer + i + 1);
  pos.x = atoi(left);
  pos.y = atoi(right);

  free(left);
  free(right);

  return pos;
}

req_t *parse_all(char *all) {
  req_t *req;
  pos_t size;
  int pos = 2;
  char str[32];

  req = create_req();
  req->symbol = all[0];
  memset(str, '\0', 32);

  pos = find_size(str, all, pos) + 2;

  size = parse_size(str);
  req->map = elem_read(all, pos, size.y, size.x);

  pos += req->map.h * (req->map.w + 1);

  pos = find_size(str, all, pos) + 2;

  size = parse_size(str);
  req->elem = elem_read(all, pos, size.y, size.x);

  return req;
}
