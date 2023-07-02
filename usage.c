#include <stdio.h>
#include <string.h>

void print_usage(void)
{
  printf("Usage: ./main [command] [options...] file1 [file2...] [options...]\n");
  printf("Commands:\n");
  printf("  create: create a file or a named pipe\n");
  printf("  read: read a file and print to stdout\n");
  printf("  write: write to a file\n");
  printf("  copy: copy a file using an unnamed pipe\n");
  printf("  info: information about a file\n");
  printf("  pipe: create a pipe and simulate communication between processes\n");
  return;
}

void print_usage_command(char *command)
{
  if (strcmp(command, "create") == 0)
  {
    printf("Usage: ./main create [-p] file perms\n");
    printf("  file: the file to create\n");
    printf("  perms: the permissions of the file\n");
    printf("  -p: create a named pipe\n");
    return;
  }
  else if (strcmp(command, "read") == 0)
  {
    printf("Usage: ./main read [file] [-o offset] [-n nBytes]\n");
    printf("  file: the file to read\n");
    printf("  -o offset: specifies the offset from where to read the file from\n");
    printf("  -n nBytes: specifies the number of bytes to read from the file\n");
    return;
  }
  else if (strcmp(command, "write") == 0)
  {
    printf("Usage: ./main write [-f] file [-o offset] [-n nBytes]\n");
    printf("  file: the file to write to\n");
    printf("  -f: force write\n");
    printf("  -o offset: specifies the offset from where to start writing\n");
    printf("  -n nBytes: specifies the number of bytes to write to the file\n");
    return;
  }
  else if (strcmp(command, "copy") == 0)
  {
    printf("Usage: ./main copy [-f] src dest\n");
    printf("  src: the source file to copy\n");
    printf("  dest: the destination file name\n");
    printf("  -f: force copy\n");
    return;
  }
  else if (strcmp(command, "pipe") == 0)
  {
    printf("Usage: ./main pipe [-u] [-f] [file] [mode]\n");
    printf("  file: the path for creating named pipe (optional) \n");
    printf("  mode: whether to open the pipe as a reader (r) or a writer (w) (if file specified)\n");
    printf("  -f: create pipe if it doesn not exist\n");
    printf("  -u: use unnamed pipe\n");
    return;
  }
  else if (strcmp(command, "info") == 0)
  {
    printf("Usage: ./main info [filename]\n");
    printf("  filename: the file to get info about\n");
    return;
  }
  else
  {
    printf("Invalid command: %s\n", command);
    print_usage();
    return;
  }
}
