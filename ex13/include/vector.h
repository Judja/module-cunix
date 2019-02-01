#include "filler.h"

#define LIMIT 1024

typedef struct possib_s {
  pos_t pos;
  int score;
} possib_t;

typedef struct  vector_s {
  possib_t* buffer;
  int size;
  int limit;
} vector_t;


vector_t*       vector_create();
void            vector_destroy(vector_t *vector);
void            vector_reset(vector_t *vector);
void            gen_p(vector_t *vector, req_t *core);
void            compute_score(vector_t *vector, req_t *core);
void            compute_dist(vector_t *vector, pos_t point);
pos_t           pick_hs(vector_t *vector);
pos_t           pick_rand(vector_t *vector);
void            vector_push(vector_t *vector, possib_t possibility);
