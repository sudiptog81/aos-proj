#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "helpers.h"

extern char buf[BUFSIZE];

int copy_file(const char *src, const char *dest, const int force_flag)
{
  int fd_src, fd_dest, n;

  if (force_flag == 0)
  {
    // check if destination file already exists
    fd_dest = open(dest, O_RDONLY);
    if (fd_dest > -1)
    {
      printf("Destination file already exists. Use -f to force copy.\n");
      close(fd_dest);
      return -1;
    }
    close(fd_dest);
  }

  // open source file
  fd_src = open(src, O_RDONLY);

  // handle error opening source file
  if (fd_src < 0)
  {
    printf("Error opening source file\n");
    return -1;
  }

  struct stat src_stat;
  stat(src, &src_stat);

  // open destination file in the same mode as source file
  fd_dest = open(dest, O_WRONLY | O_TRUNC | O_CREAT, src_stat.st_mode);

  // handle error opening destination file
  if (fd_dest < 0)
  {
    printf("Error opening destination file\n");
    return -1;
  }

  // create pipe
  int pipefd[2];
  pipe(pipefd);

  // fork process
  pid_t pid = fork();

  if (pid > 0) // parent process
  {
    close(pipefd[0]);
    flush_buffer(buf);

    // read from source file and write to pipe
    while ((n = read(fd_src, buf, BUFSIZE)) > 0)
    {
      write(pipefd[1], buf, n);
      flush_buffer(buf);
    }

    close(pipefd[1]);
  }
  else if (pid == 0) // child process
  {
    close(pipefd[1]);
    flush_buffer(buf);

    // read from pipe and write to destination file
    while ((n = read(pipefd[0], buf, BUFSIZE)) > 0)
    {
      write(fd_dest, buf, n);
      flush_buffer(buf);
    }

    close(pipefd[0]);
    exit(0);
  }
  else
  {
    printf("Error forking process\n");
    return -1;
  }

  // close files
  close(fd_src);
  close(fd_dest);

  printf("Copied %s to %s...\n", src, dest);

  return 0;
}
