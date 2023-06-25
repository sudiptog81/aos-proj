#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "helpers.h"

extern char buf[1024];

int copy_file(const char *src, const char *dest, const int force_flag)
{
  int fd_src, fd_dest, n;

  if (force_flag == 0)
  {
    fd_dest = open(dest, O_RDONLY);
    if (fd_dest > -1)
    {
      printf("Destination file already exists. Use -f to force copy.\n");
      close(fd_dest);
      return -1;
    }
    close(fd_dest);
  }

  fd_src = open(src, O_RDONLY);

  if (fd_src < 0)
  {
    printf("Error opening source file\n");
    return -1;
  }

  struct stat src_stat;
  stat(src, &src_stat);

  fd_dest = open(dest, O_WRONLY | O_TRUNC | O_CREAT, src_stat.st_mode);

  if (fd_dest < 0)
  {
    printf("Error opening destination file\n");
    return -1;
  }

  flush_buffer(buf);

  while (read(fd_src, buf, sizeof(buf)) > 0)
  {
    write(fd_dest, buf, strlen(buf));
    flush_buffer(buf);
  }

  close(fd_src);
  close(fd_dest);

  printf("Copied %s to %s...\n", src, dest);

  return 0;
}
