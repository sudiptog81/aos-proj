#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "helpers.h"

extern char buf[BUFSIZE];

int read_file(const char *path, const int offset, const int nBytes)
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

  // seek to offset and handle errors
  if (lseek(fd, offset, SEEK_SET) < 0)
  {
    printf("Error seeking to offset\n");
    return -1;
  }

  // read file content to buffer and write to stdout
  // also keep track of total bytes read
  if (nBytes < 0)
  {
    // read entire file
    while ((n = read(fd, buf, sizeof(buf))) > 0)
    {
      for (int i = 0; i < n; i++)
      {
        printf("%c", buf[i]);
      }
      flush_buffer(buf);
      tot += n;
    }
  }
  else
  {
    // read nBytes from file
    n = read(fd, buf, nBytes);
    for (int i = 0; i < n; i++)
    {
      printf("%c", buf[i]);
    }
    flush_buffer(buf);
    tot += n;
  }

  // housekeeping
  close(fd);

  // retuirn total bytes read
  return tot;
}
