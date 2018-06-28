#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <stdio.h>
#include "filler.h"
#include "my_string.h"

#define BUF_SIZE 64

void read_input(filler_t* filler) {
  char str[BUF_SIZE];
  int num_of_read;

  num_of_read = 0;

  while(1){
    memset(str, '\0', BUF_SIZE);
    num_of_read = read(0, str, BUF_SIZE - 1);

    if(!filler->current_stream)
      filler->current_stream = string_create(str);
    else
      string_append(filler->current_stream, str);

    if(num_of_read <= 0)
      break;
  }
}

int read_is_finished(stream_t* buf) {
  int pos = 0;
  bool first_size = true;
  int elem_pos = 0;
  char arr_elem_size[32];
  pos_t el_size;

  while(pos <= buf->size) {
    if(buf->str[pos] > '9' || buf->str[pos] < '0')
      pos++;
    else if(first_size) {
      while(pos <= buf->size && buf->str[pos] != '\n')
        pos++;
      pos++;
      first_size = false;
    }
    else {
      elem_pos = pos;
      while(pos <= buf->size && buf->str[pos] != '\n')
        pos++;
      if(buf->str[pos] != '\n')
        return -1;
      else {
        find_size(arr_elem_size, buf->str, elem_pos);
        el_size = parse_size(arr_elem_size);
        if(buf->size <= pos + el_size.x*(el_size.y + 1))
          return -1;
        else return 0;
      }
    }
  }
  
  return -1;
}

req_t *read_request(filler_t *filler) {
  req_t *req;

  read_input(filler);

  if(read_is_finished(filler->current_stream) == 0)
    req = parse_all(filler->current_stream->str);

  return req;
}
