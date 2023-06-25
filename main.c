#include <string.h>

#include "helpers.h"
#include "syscalls.h"
#include "usage.h"

char buf[1024];

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
    if (argc < 3)
    {
      print_usage_command("read");
      return -1;
    }

    if (read_file(argv[2]) == -1)
      return -1;
    break;

  case 1:
    if (argc < 3)
    {
      print_usage_command("write");
      return -1;
    }

    if (argc == 4)
    {
      if (strcmp(argv[2], "-f") != 0)
      {
        print_usage_command("write");
        return -1;
      }

      if (write_file(argv[3], 1) == -1)
        return -1;
    }
    else if (argc == 3)
    {
      if (write_file(argv[2], 0) == -1)
        return -1;
    }
    break;
  case 2:
    if (argc != 4 && argc != 5)
    {
      print_usage_command("copy");
      return -1;
    }

    if (argc == 5)
    {
      if (strcmp(argv[2], "-f") != 0)
      {
        print_usage_command("copy");
        return -1;
      }

      if (copy_file(argv[3], argv[4], 1) == -1)
        return -1;
    }
    else if (argc == 4)
    {
      if (copy_file(argv[2], argv[3], 0) == -1)
        return -1;
    }
    break;
  case 3:
    if (argc != 2 && argc != 4)
    {
      print_usage_command("pipe");
      return -1;
    }

    if (argc == 2)
    {
      if (unnamed_pipe() == -1)
        return -1;
      break;
    }
    else
    {

      if (strcmp(argv[3], "r") == 0)
      {
        if (named_pipe(argv[2], 1) == -1)
          return -1;
        break;
      }
      else if (strcmp(argv[3], "w") == 0)
      {
        if (named_pipe(argv[2], 0) == -1)
          return -1;
        break;
      }
    }

    break;

    // ./main pipe n.pipe w
    // ./main pipe n.pipe r

    // ./main pipe
  case 4:
    if (argc != 4 && argc != 5)
    {
      print_usage_command("create");
      return -1;
    }

    if (argc == 5)
    {
      if (strcmp(argv[2], "-f") != 0)
      {
        print_usage_command("create");
        return -1;
      }

      if (create_file(argv[3], parse_perms(argv[4]), 1) == -1)
        return -1;
      break;
    }
    else if (argc == 4)
    {
      if (create_file(argv[2], parse_perms(argv[3]), 0) == -1)
        return -1;
      break;
    }
    break;

    // ./main create -f file.txt 777
    // ./main create file.txt 777
  default:
    print_usage();
    return -1;
  }

  return 0;
}
