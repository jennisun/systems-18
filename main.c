#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>

#define READ 0
#define WRITE 1

int main() {

  int parent[2];
  pipe(parent);
  printf("pipe created. parent[0]: %d parent[1]: %d\n", parent[0], parent[1]);

  int f;
  f = fork();

  if (f) {
    //parent
    close(parent[WRITE]);
    char line[10];
    while (read(parent[READ], line, sizeof(line))) {
      printf("parent got: [%s]\n", line);
    }
  }
  else {
    //child
    close(parent[READ]);
    sleep(2);

    char line[1000];
    while(fgets(line, 1000, stdin)) {
      line[strlen(line) - 1] = '\0';
      write(parent[WRITE], line, strlen(line));
      sleep(2);
    }
  }
  return 0;
}
