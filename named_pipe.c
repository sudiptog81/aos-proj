#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "helpers.h"

extern char buf[BUFSIZE];

int named_pipe(const char *path, const int read_flag, const int force_flag)
{

  int n, fd;
  char *string;
  size_t len = BUFSIZE;

  if (read_flag == 0) // open named pipe for writing
  {
    fd = open(path, O_WRONLY);

    if (force_flag == 0)
    {
      if (fd < 0)
      {
        n = mknod(path, __S_IFIFO | 0666, 0);

        if (n < 0)
        {
          printf("Error creating named pipe\n");
          return -1;
        }

        fd = open(path, O_WRONLY);
      }
    }
    else
    {
      if (fd > -1)
      {
        unlink(path);
      }

      n = mknod(path, __S_IFIFO | 0666, 0);

      if (n < 0)
      {
        printf("Error creating named pipe\n");
        return -1;
      }

      fd = open(path, O_WRONLY);
    }

    printf("type :q to exit\n----------------\n");

    // read from stdin and write to named pipe until :q is entered
    while (1)
    {
      printf("Message: ");

      string = (char *)(malloc(sizeof(char) * len));
      flush_buffer(string);

      getline(&string, &len, stdin);
      write(fd, string, strlen(string) - 1);

      if (strcmp(string, ":q\n") == 0)
      {
        break;
      }

      free(string);
    }

    free(string);
    close(fd);
  }
  else // open named pipe for reading
  {
    fd = open(path, O_RDONLY);

    if (fd < 0)
    {
      printf("Error opening named pipe for reading...\n");
      return -1;
    }

    printf("Waiting for writer...\n");

    // read from named pipe until :q is received
    while (1)
    {
      flush_buffer(buf);

      read(fd, buf, sizeof(buf));

      if (strcmp(buf, ":q") == 0)
      {
        printf("Received Bye...\n");
        break;
      }

      printf("Received: %s\n", buf);
    }
    close(fd);
  }

  return 0;
}
