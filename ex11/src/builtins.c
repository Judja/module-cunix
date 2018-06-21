#include "minishell.h"

int export(hashtable_t* env, const char *args) {
  char *var, *value, *var_ptr, *value_ptr;

  var = malloc(32 * sizeof(char));
  value = malloc(128 * sizeof(char));
  var_ptr = var;
  value_ptr = value;

  while (*args != '\0' && *args != '=' && *args != ' ')
    *var++ = *args++;

  *var = '\0';
  while(*args  == ' ') args++;
  if (*args == '\0' || *args != '=') return -1;
  args++;//skip '='
  while(*args  == ' ') args++;
  while(1) {
    if(*args == ' ' || *args == '\0') {
      *value = '\0';
      hash_set(env, var_ptr, value_ptr);

      return 0;
    }
    *value++ = *args++;
  }

  return -1;
}

int env(hashtable_t* env) {
  hash_print(env);

  return 0;
}
