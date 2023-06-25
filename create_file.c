#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "helpers.h"

extern char buf[1024];

int create_file(const char *path, const int perms, const int force_flag)
{
  int fd;

  if (force_flag == 0)
  {
    fd = open(path, O_RDONLY);
    if (fd != -1)
    {
      printf("File already exists. Use -f to force create.\n");
      close(fd);
      return -1;
    }
  }

  umask(0);
  fd = creat(path, perms);
  close(fd);

  return 0;
}
