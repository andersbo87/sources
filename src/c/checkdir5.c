#include <stdio.h>
#include <sys/stat.h>
 
int isDir(const char *dname);
 
int main(int argc, char *argv[]) {
 
  if (argc != 2) { 
    printf("Usage: %s directory name\n", argv[0]); 
    exit(0);
  }
 
  if(isDir(argv[1])) {
    printf("%s is a directory.\n", argv[1]);
  }
 
return 0;
}
 
int isDir(const char *dname) {
  struct stat sbuf;
 
  if (lstat(dname, &sbuf) == -1) {
    fprintf(stderr, "lstat() Failed.\n");
    return 0;
  }
 
  if(S_ISDIR(sbuf.st_mode)) {
    return 1;
  }
 
return 0;
}
