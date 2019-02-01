#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include "hash.h"
#include "builtins.h"

/*                                    Hints
 * Use "$_>" for prompt
 *
 * Note: if you want to use a hash to store shell vars, you must modify
 * both hash and linked_list to store keys, not only data
 *
 * It is better to start with export
 *
 * To print vars with env use next format:
 * "var_name: var_value"
 *
 * For ls use next format(printing in one line with one space as a delimiter):
 * "file1 file2 file3 "
 *
 * Use signal handler to handle Ctrl-C
 *
 *
 * Good luck)
 *
 */

#endif
