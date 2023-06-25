#include <stdio.h>
#include <string.h>

void print_usage(void)
{
  printf("Usage: ./main [command] [options...] file1 [file2...]\n");
  printf("Commands:\n");
  printf("  create: create a file\n");
  printf("  read: read a file and print to stdout\n");
  printf("  write: write to a file\n");
  printf("  copy: copy a file\n");
  printf("  pipe: create a pipe and simulate message passing\n");
  return;
}

void print_usage_command(char *command)
{
  if (strcmp(command, "create") == 0)
  {
    printf("Usage: ./main create [file] [perms]\n");
    printf("  file: the file to create\n");
    printf("  perms: the permissions of the file\n");
    return;
  }
  else if (strcmp(command, "read") == 0)
  {
    printf("Usage: ./main read [file]\n");
    printf("  file: the file to read\n");
    return;
  }
  else if (strcmp(command, "write") == 0)
  {
    printf("Usage: ./main write [-f] [file]\n");
    printf("  file: the file to write to\n");
    printf("  -f: force write\n");
    return;
  }
  else if (strcmp(command, "copy") == 0)
  {
    printf("Usage: ./main copy -f [src] [dest]\n");
    printf("  src: the source file to copy\n");
    printf("  dest: the destination file name\n");
    printf("  -f: force copy\n");
    return;
  }
  else if (strcmp(command, "pipe") == 0)
  {
    printf("Usage: ./main pipe [file] [mode]\n");
    printf("  file: the path for creating named pipe (optional) \n");
    printf("  mode: whether to open the pipe as a reader (r) or a writer (w) (if file specified)\n");
    return;
  }
}
