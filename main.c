#include <string.h>

#include "helpers.h"
#include "syscalls.h"
#include "usage.h"

char buf[BUFSIZE];

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    print_usage();
    return -1;
  }

  flush_buffer(buf);

  switch (parse_command(argv[1]))
  {
  case 0:
    if (argc < 3 || argc > 7)
    {
      print_usage_command("read");
      return -1;
    }

    if (argc == 3 && read_file(argv[2], 0, -1) == -1)
    {
      return -1;
    }
    else if (argc == 5 && strcmp(argv[3], "-o") == 0 && read_file(argv[2], atoi(argv[4]), -1) == -1)
    {
      return -1;
    }
    else if (argc == 5 && strcmp(argv[3], "-n") == 0 && read_file(argv[2], 0, atoi(argv[4])) == -1)
    {
      return -1;
    }
    else if (argc == 7 && strcmp(argv[3], "-o") == 0 && strcmp(argv[5], "-n") == 0 && read_file(argv[2], atoi(argv[4]), atoi(argv[6])) == -1)
    {
      return -1;
    }

    break;

  case 1:
    if (argc < 3 || argc > 8)
    {
      print_usage_command("write");
      return -1;
    }

    if (argc == 4 && strcmp(argv[2], "-f") != 0)
    {
      print_usage_command("write");
      return -1;
    }

    if (argc == 3 && write_file(argv[2], 0, -1, 0) == -1)
    {
      return -1;
    }
    else if (argc == 4 && write_file(argv[3], 0, -1, 1) == -1)
    {
      return -1;
    }
    else if (argc == 5 && strcmp(argv[3], "-o") == 0 && write_file(argv[2], atoi(argv[4]), -1, 0) == -1)
    {
      return -1;
    }
    else if (argc == 5 && strcmp(argv[3], "-n") == 0 && write_file(argv[2], 0, atoi(argv[4]), 0) == -1)
    {
      return -1;
    }
    else if (argc == 6 && strcmp(argv[2], "-f") == 0 && strcmp(argv[4], "-o") == 0 && write_file(argv[3], atoi(argv[5]), -1, 1) == -1)
    {
      return -1;
    }
    else if (argc == 6 && strcmp(argv[2], "-f") == 0 && strcmp(argv[4], "-n") == 0 && write_file(argv[3], 0, atoi(argv[5]), 1) == -1)
    {
      return -1;
    }
    else if (argc == 7 && strcmp(argv[3], "-o") == 0 && strcmp(argv[5], "-n") == 0 && write_file(argv[2], atoi(argv[4]), atoi(argv[6]), 0) == -1)
    {
      return -1;
    }
    else if (argc == 8 && strcmp(argv[2], "-f") == 0 && strcmp(argv[4], "-o") == 0 && strcmp(argv[6], "-n") == 0 && write_file(argv[3], atoi(argv[5]), atoi(argv[7]), 1) == -1)
    {
      return -1;
    }

    break;

  case 2:
    if (argc != 4 && argc != 5)
    {
      print_usage_command("copy");
      return -1;
    }

    if (argc == 5 && strcmp(argv[2], "-f") != 0)
    {
      print_usage_command("copy");
      return -1;
    }

    if (argc == 5 && copy_file(argv[3], argv[4], 1) == -1)
      return -1;
    else if (copy_file(argv[2], argv[3], 0) == -1)
      return -1;
    break;

  case 3:
    if (argc < 3 || argc > 5)
    {
      print_usage_command("pipe");
      return -1;
    }

    if (argc == 3 && strcmp(argv[2], "-u") != 0)
    {
      print_usage_command("pipe");
      return -1;
    }
    else if (argc == 3 && strcmp(argv[2], "-u") == 0)
    {
      return unnamed_pipe();
    }
    else if (argc == 5 && strcmp(argv[2], "-f") == 0 && strcmp(argv[4], "r") == 0)
    {
      return named_pipe(argv[3], 1, 0);
    }
    else if (argc == 5 && strcmp(argv[2], "-f") == 0 && strcmp(argv[4], "w") == 0)
    {
      return named_pipe(argv[3], 0, 0);
    }
    else if (argc == 4 && strcmp(argv[2], "-f") != 0 && strcmp(argv[3], "r") == 0)
    {
      return named_pipe(argv[2], 1, 0);
    }
    else if (argc == 4 && strcmp(argv[2], "-f") != 0 && strcmp(argv[3], "w") == 0)
    {
      return named_pipe(argv[2], 0, 0);
    }
    else
    {
      print_usage_command("pipe");
      return -1;
    }

    break;

  case 4:
    if (argc != 4 && argc != 5)
    {
      print_usage_command("create");
      return -1;
    }

    if (argc == 5 && strcmp(argv[2], "-f") != 0 && strcmp(argv[2], "-p") != 0)
    {
      print_usage_command("create");
      return -1;
    }

    if (argc == 5 && strcmp(argv[2], "-f") == 0)
    {
      if (create_file(argv[3], parse_perms(argv[4]), 0, 1) == -1)
        return -1;
    }
    else if (argc == 5 && strcmp(argv[2], "-p") == 0)
    {
      if (create_file(argv[3], parse_perms(argv[4]), 1, 1) == -1)
        return -1;
    }
    else if (create_file(argv[2], parse_perms(argv[3]), 0, 0) == -1)
      return -1;
    break;

  case 5:
    if (argc != 3)
    {
      print_usage_command("info");
      return -1;
    }
    stat_file(argv[2]);
    break;

  default:
    print_usage();
    return -1;
  }

  return 0;
}
