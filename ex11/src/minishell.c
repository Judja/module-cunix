#include "minishell.h"

/*
 * Works:
 * Redirection to file (>)
 * Vars subtitution ($)
 * looking for binaries in own PATH
 * echo and ls are binaries
 * export and env are built-ins
 */

int process_vars(hashtable_t *ht, char **input) {
  char *iptr, *str_ptr, *str;
  char *word, *word_ptr;

  str_ptr = malloc(512 * sizeof(char));
  word_ptr = malloc(32 * sizeof(char));
  iptr = *input;
  str = str_ptr;
  while(*iptr != '\0') {
    if (*iptr == '$') {
      iptr++;
      word = word_ptr;
      while(*iptr != ' ' && *iptr != '\0')
        *word++ = *iptr++;
      *word = '\0';
      word = (char *)hash_get(ht, word_ptr);
      if(!word)
        continue;
      while(*word != '\0')
        *str++ = *word++;
      continue;
    }
    *str++ = *iptr++;
  }
  *str = '\0';
  *input = str_ptr;

  return 0;
}

int	get_input(hashtable_t *ht) {
	int	ret, i = 0, count = 1;
	char buf, *input, *ptr;

  input = (char *)malloc(512 * sizeof(char));
  ptr = input;

	while ((ret = read(0, &buf, 1)) && buf != '\n') {
		*(input + i++)= buf;
		count++;
	}
  if (count < 2) return 0;
  while(*(input + i) == ' ')
    i--;
	*(input + i + 1) = '\0';
	if (!ret) {
    free(ptr);
    return 1;
	}
  if(process_vars(ht, &ptr) != 0)
    write(1, "error", 5);

  return exec(ht,ptr);
}

void	display_msg(void) {
  write(1,"$_>", 3);
}

void	signal_handler(int signo) {
	if (signo == SIGINT) {
    write(1, "\n", 1);
  	display_msg();
		signal(SIGINT, signal_handler);
	}
}

int main() {
  hashtable_t *ht;
  char cwd[1024];
  int status;

  ht = hash_create(64);
  getcwd(cwd, sizeof(cwd));
  strcat(cwd, "/bin/");
  hash_set(ht, "PATH", cwd);

  do {
    display_msg();
    signal(SIGINT, signal_handler);
    status = get_input(ht);
  } while (status == 0);

  write(1, "\n", 1);

  return 0;
}
