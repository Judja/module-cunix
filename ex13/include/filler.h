#ifndef _FILLER_H_
#define _FILLER_H_

#define BUF_SIZE 1024

typedef struct elem_s
{
  int           h;
  int           w;
  char          **array;
}               elem_t;

typedef struct  pos_s
{
  int           x;
  int           y;
}               pos_t;

typedef struct  req_s
{
  char          symbol;
  elem_t        map;
  elem_t        elem;
}               req_t;

typedef struct  stream_s
{
  char          *str;
  int           size;
  int           limit;
}               stream_t;

typedef struct  filler_s
{
  struct        vector_s *possibilities;
  stream_t      *current_stream;
  int           status;
  int           l_most;
  int           r_most;
  int           t_most;
  int           b_most;
  pos_t			    (*strategy)(req_t *req, struct filler_s *filler);
}               filler_t;

/*Functions for reading*/
req_t*          read_request(filler_t *filler);
void            read_input(filler_t* filler);

/*Functions for parsing*/
req_t*          parse_all(char *all);
pos_t           parse_size(char *answer);
int             find_size(char *dist, char *source, int start);

elem_t          elem_init(int width, int height);
elem_t          elem_read(char *source, int pos, int w, int h);
void            elem_destroy(elem_t *elem);


/*Functions for game logic*/
void            start_game(filler_t *filler);
pos_t           play(req_t *core, filler_t *filler);
int             check_free_space(elem_t *map, elem_t *new_elem, pos_t pos);
int             check_connection(elem_t *map, elem_t *new_elem, pos_t pos, char symbol);
int             check_placable(elem_t *map, elem_t *new_elem, pos_t pos, char symbol);

/*Functions for printing*/
void            print_pos(pos_t p);

/*Tools*/
int             set_nonblocking(int fd);
void            fatal(char *msg);

void            create_filler(filler_t *filler);
void            destroy_filler(filler_t *filler);
req_t           *create_req();
void            destroy_req(req_t *req);
void            log_init();
void            my_log(char *str);
void            my_log_f(char *format, ...);
/*Strategies*/
pos_t           init_strategy(req_t *core, filler_t *filler);
pos_t           hs(req_t *core, filler_t *filler);
pos_t           randm(req_t *core, filler_t *filler);
#endif // _FILLER_H_
