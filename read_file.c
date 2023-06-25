#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "helpers.h"

extern char buf[1024];

int read_file(const char *path)
{
  long tot = 0;
  flush_buffer(buf);

  // open file descriptor and handle errors
  int n, fd = open(path, O_RDONLY);
  if (fd < 0)
  {
    printf("Error opening file\n");
    return -1;
  }

  // read file content to buffer and write to stdout
  // also keep track of total bytes read
  while ((n = read(fd, buf, sizeof(buf))) > 0)
  {
    printf("%s", buf);
    flush_buffer(buf);
    tot += n;
  }

  // housekeeping
  close(fd);

  // retuirn total bytes read
  return tot;
}
