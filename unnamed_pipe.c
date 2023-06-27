#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "helpers.h"

extern char buf[1024];

int unnamed_pipe(void)
{
  pid_t pid;
  int n, fd[2];
  char *string;
  size_t len = 1024;

  // create unnamed pipe
  if (pipe(fd) < 0)
  {
    printf("Error creating pipe\n");
    return -1;
  }

  // fork process
  if ((pid = fork()) < 0)
  {
    printf("Error forking\n");
    return -1;
  }

  if (pid > 0) // parent process
  {
    close(fd[0]);

    printf("type :q to exit\n----------------\n");

    // read from stdin and write to pipe until :q is entered
    while (1)
    {
      printf("Message: ");

      string = (char *)(malloc(sizeof(char) * len));
      flush_buffer(string);

      getline(&string, &len, stdin);
      write(fd[1], string, strlen(string) - 1);

      if (strcmp(string, ":q\n") == 0)
      {
        break;
      }

      free(string);
      sleep(1);
    }

    free(string);
    close(fd[1]);
  }
  else if (pid == 0) // child process
  {
    close(fd[1]);

    // read from pipe until :q is received
    while (1)
    {
      flush_buffer(buf);
      read(fd[0], buf, sizeof(buf));

      if (strcmp(buf, ":q") == 0)
      {
        printf("Received Bye from Parent...\n");
        exit(0);
      }

      printf("Received from Parent: %s\n", buf);
    }

    close(fd[0]);
  }

  return 0;
}
