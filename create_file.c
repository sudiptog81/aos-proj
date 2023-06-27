#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "helpers.h"

extern char buf[1024];

int create_file(const char *path, const int perms, const int pipe_flag, const int force_flag)
{
  int fd;

  if (force_flag == 0)
  {
    // check if file already exists
    fd = open(path, O_RDONLY);
    if (fd != -1)
    {
      printf("File already exists. Use -f to force create.\n");
      close(fd);
      return -1;
    }
  }

  // set umask to 0 to ensure that the file is created with the permissions specified
  umask(0);

  if (!pipe_flag) // create regular file
  {
    fd = creat(path, perms);

    if (fd < 0)
    {
      printf("Error creating file\n");
      return -1;
    }

    fd = open(path, O_WRONLY);
  }
  else // create named pipe
  {
    fd = mknod(path, __S_IFIFO | perms, 0);

    if (fd < 0)
    {
      printf("Error creating named pipe\n");
      return -1;
    }
  }

  close(fd);

  return 0;
}
