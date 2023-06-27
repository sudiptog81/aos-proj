#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "helpers.h"

int write_file(const char *path, const int offset, const int nBytes, const int force_flag)
{
  int n, fd;
  char *string;
  size_t len = 1024;

  // check if file exists when -f is not used
  if (force_flag == 0)
  {
    fd = open(path, O_WRONLY);
    if (fd > -1)
    {
      printf("Destination file already exists. Use -f to force write.\n");
      close(fd);
      return -1;
    }
    else
    {
      fd = open(path, O_WRONLY | O_CREAT, 0644);
    }
  }
  // create file if it doesn't exist when -f is used
  else
  {
    fd = open(path, O_WRONLY | O_TRUNC | O_CREAT, 0644);
  }

  // handle errors in opening file
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

  if (nBytes < 0)
  {
    printf("type :w to exit\n---------------\n");
    while (1)
    {
      // allocate memory for string
      string = (char *)(malloc(sizeof(char) * len));
      flush_buffer(string);

      // get input from stdin
      getline(&string, &len, stdin);

      // exit if :w is typed
      if (strcmp(string, ":w\n") == 0)
      {
        break;
      }

      // write string to file and free memory for string
      write(fd, string, strlen(string));
      free(string);
    }
  }
  else
  {
    // allocate memory for string
    string = (char *)(malloc(sizeof(char) * nBytes));
    flush_buffer(string);

    // get input from stdin
    n = read(STDIN_FILENO, string, nBytes + 1);

    // write string to file and free memory for string
    write(fd, string, n);
  }

  // free memory for string and close file descriptor
  free(string);
  close(fd);

  return 0;
}
