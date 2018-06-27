#ifndef _FILLER_H_
#define _FILLER_H_

#define BUF_SIZE 64

typedef struct content_s
{
  int           h;
  int           w;
  char          **array;
}               content_t;

typedef struct  pos_s
{
  int           x;
  int           y;
}               pos_t;

typedef struct  req_s
{
  char          symbol;
  content_t         map;
  content_t         elem;
}               req_t;

typedef struct  stream_s
{
  char          *str;
  unsigned int  size;
  unsigned int  limit;
}               stream_t;

typedef struct  filler_s
{
  stream_t      *current_stream;
  int           status;
  int           find_enemy;
}               filler_t;

/*Functions for reading*/
req_t*          read_request(filler_t *filler);
void            read_input(filler_t* filler);

/*Functions for parsing*/
req_t*          parse_all(char *all);
pos_t           parse_size(char *answer);
int             find_size(char *dist, char *source, int start);

content_t       content_init(int width, int height);
content_t       content_read(char *source, int pos, int w, int h);
void            content_destroy(content_t *content);


/*Functions for game logic*/
void            start_game(filler_t *filler);
pos_t           play(req_t *core);

/*Functions for printing*/
void            print_pos(pos_t p);

/*Tools*/
int             set_nonblocking(int fd);
void            fatal(char *msg);

void            create_filler(filler_t *filler);
void            destroy_filler(filler_t *filler);
req_t           *create_req();
void            destroy_req(req_t *req);
void            printlog(const char *filename, const char *mode, const char *format, ...);
void            log_init();
void            my_log(char *str);
void 			my_log_f(char *format, ...);
#endif // _FILLER_H_
