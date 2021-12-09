#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>

#define READ 0
#define WRITE 1

int main() {
  int child[2];
  int parent[2];
  pipe(child);
  pipe(parent);

  int f;
  char line[1000];
  f = fork();

  if (f) {
    //parent
    close(child[READ]);
    close(parent[WRITE]);

    while(1) {
      printf("Enter input: ");
      fgets(line, 1000, stdin);
      line[strlen(line) - 1] = '\0';
      write(child[WRITE], line, sizeof(stdin));
      // sleep(3);
      read(parent[READ], line, sizeof(stdin));
      printf("Parent got: [%s]\n", line);
    }
  }
  else {
    //child
    close(child[WRITE]);
    close(parent[READ]);

    while (read(child[READ], line, sizeof(line))) {
      int len = strlen(line);
      char line1[len];
      for (int i = 0; i < len; i ++) {
        line1[len - 1 - i] = line[i];
      }
      line1[len] = '\0';
      write(parent[WRITE], line1, sizeof(line1));
    }
  }
  return 0;
}
