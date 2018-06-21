#include "minishell.h"

int exec(hashtable_t* ht, char *input) {
  char *ptr = input;
  while(*ptr != '\0') {
    //if (*ptr == '|') return exec_with_pipe(ht, input);
    if(*ptr == '>') {
      int i = -1;
      while(*(ptr + i) == ' ')
        i--;
      *(ptr + i + 1) = '\0';
      ptr++;//skipping '>'
      while(*ptr == ' ') {ptr++;}

      char *file_name, *file_name_ptr;

      file_name = malloc(32 * sizeof(char));
      file_name_ptr = file_name;

      while(*ptr != '\0' && *ptr != ' ') *file_name_ptr++ = *ptr++;

      return exec_command_to_file(ht, input, file_name);
    }
    ptr++;
  }

  return exec_command(ht, input);
}

int exec_command(hashtable_t *ht,char *input) {
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

  if (strcmp("env", str_ptr) == 0)
    env(ht);
  else if (strcmp("export", str_ptr) == 0)
    export(ht, input);
  else if (strcmp("exit", str_ptr) == 0)
    return 1;
  else if(strcmp("ls", str_ptr) == 0 || strcmp("echo", str_ptr) == 0) {
    int pid = fork();
    if (pid == 0) {
      execl(str_ptr, str_ptr, input, NULL);
    }
    else {
      wait(NULL);
    }
  }
  else
    printf("Command not found: %s\n", str_ptr);

  write(1, "\n", 1);
  return 0;
}

int exec_command_to_file(hashtable_t *ht,char *input, char* file) {
     int out = open(file, O_RDWR|O_CREAT|O_TRUNC, 0600);
     if (-1 == out) { perror("opening cout.log"); return 255; }

      int save_out = dup(fileno(stdout));
      if (-1 == dup2(out, fileno(stdout))) { perror("cannot redirect stdout"); return 255; }

      exec_command(ht, input);

      fflush(stdout); close(out);
      dup2(save_out, fileno(stdout));
      close(save_out);

  return 0;
}

/*int exec_with_pipe(hashtable_t* env, char* input) {
  char *fcmd, *scmd;
  int i = 0;

  int save_out = dup(fileno(stdout));
  int save_in = dup(fileno(stdin));

  fcmd = input;
  while(*input != '|')
    *(fcmd + i++) = *input++;
  i--;
  while(*(fcmd + i) == ' ')
       i--;
  *(fcmd + i + 1) = '\0';

  input++;
  while(*input == ' ') input++;
  if(*input == '\0')
    return 1;
  i = 0;
  scmd = input;

    int p[2];
    pipe(p); // Creates a pipe with file descriptors Eg. input = 3 and output = 4 (Since, 0,1 and 2 are not available)

    int pid = fork();
    if (pid == 0) {
    // Child process
        close(0); // Release fd no - 0
        close(p[0]); // Close pipe fds since useful one is duplicated
        close(p[1]);
        dup(p[0]); // Create duplicate of fd - 3 (pipe read end) with fd 0.
        exec(env, scmd);
    } else {
        //Parent process
        close(1); // Release fd no - 1
        close(p[0]); // Close pipe fds since useful one is duplicated
        close(p[1]);
        dup(p[1]); // Create duplicate of fd - 4 (pipe write end) with fd 1.
        exec(env, fcmd);
    }

    dup2(save_out, fileno(stdout));
    close(save_out);
    dup2(save_in, fileno(stdin));
    close(save_in);

  return 0;
}*/