#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "hash.h"

char **g_envv;

void	exit_shell(void) {
	free(g_envv);
	write(1, "\n", 1);
	exit(0);
}

void	init_envv(int args, char **argv, char **envv) {
	int		i;
	(void)args;
	(void)argv;
	g_envv = (char **)malloc(sizeof(char *) * (strlen(*envv) + 1));
	i = -1;
	while (envv[++i]) {
		if (!(g_envv[i] = strdup(envv[i])))
			exit_shell();
	}
}

void exec_command(hashtable_t *ht,char *input) {
  char *str, *str_ptr;

  str = malloc(32 * sizeof(char));
  str_ptr = str;

  while(*input != '\0') {
    if(*input == ' ') {
      *str = '\0';
      input++;
      break;
    }
    *str++ = *input++;
  }
  *str = '\0';
  printf("%s\n", str_ptr);
}

static void	 get_input(hashtable_t *ht) {
	int		ret;
	char	buf;
	int		i;
	int		count;
  char *input = (char *)malloc(512 * sizeof(char));
  char *ptr = input;
	count = 1;
	i = 0;
	while ((ret = read(0, &buf, 1)) && buf != '\n') {
		*(input + i++)= buf;
		count++;
	}
	*(input + i) = '\0';
	if (!ret) {
    free(ptr);
		exit_shell();
	}
  exec_command(ht,ptr);
}

void	display_msg(void) {
	char	*cwd;
	char	buff[512];
	char	*parsed_cwd;

	cwd = getcwd(buff, 511);
  write(1,cwd,strlen(cwd));
  write(1, " $ ",strlen(" $ "));
}

void	signal_handler(int signo) {
	if (signo == SIGINT) {
		puts("");
  	display_msg();
		signal(SIGINT, signal_handler);
	}
}

int main(int argc, char **argv, char **envv) {
  int		ret;
  char	**commands;
  hashtable_t *ht;
  init_envv(argc,argv,envv);
  while(1) {
    display_msg();
    signal(SIGINT, signal_handler);
    get_input(ht);
  }

  free(g_envv);

  return 0;
}
