#ifndef BUILTINS_H_
#define BUILTINS_H_

#include "hash.h"

int export(hashtable_t* env, const char* args);

int env(hashtable_t* env);

int exec(hashtable_t* env, char* input);

int exec_command(hashtable_t* env, char* input);

int exec_command_to_file(hashtable_t* env, char* input, char* file);

int exec_with_pipe(hashtable_t* env, char* input);

#endif