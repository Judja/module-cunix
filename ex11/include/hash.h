#ifndef   HASH_H_
# define  HASH_H_

typedef struct  hashtable {
  int  size;
  void          **table;
  // int           backend_type; //0 noop for test, 1 linkedlist, 2 tree
  //void          (*fcreate)();
  //void          (*fseek)(char *key);
  //void          (*fdestroy)();
  //void          (*fhash)(char *k);
}               hashtable_t;

hashtable_t     *hash_create(int size);
void            hash_destroy(hashtable_t *ht);
unsigned int    hash_func(char *key);

void            hash_set(hashtable_t *ht, char *key, void *ptr);
const void      *hash_get(hashtable_t *ht, char *key);
void            hash_print(hashtable_t *ht);

#endif
