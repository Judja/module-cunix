#include<stdio.h>
#include <dirent.h>
#include <string.h>

void main(int argc, char* argv[]) {
  DIR *dir;
  struct dirent *dent;
  dir = opendir(argv[1]);
  if(dir!=NULL) {
    while((dent=readdir(dir))!=NULL) {
      if((strcmp(dent->d_name,".")==0 || strcmp(dent->d_name,"..")==0 || (*dent->d_name) == '.' )) {}
      else {
        write(1, dent->d_name, strlen(dent->d_name));
        write(1, " ", 1);
      }
    }
  }
  close(dir);
}