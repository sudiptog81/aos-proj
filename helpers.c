#include <stdio.h>
#include <string.h>

int parse_command(const char *command)
{
  if (strcmp(command, "read") == 0)
  {
    return 0;
  }
  else if (strcmp(command, "write") == 0)
  {
    return 1;
  }
  else if (strcmp(command, "copy") == 0)
  {
    return 2;
  }
  else if (strcmp(command, "pipe") == 0)
  {
    return 3;
  }
  else if (strcmp(command, "create") == 0)
  {
    return 4;
  }
  else if (strcmp(command, "info") == 0)
  {
    return 5;
  }
  else
  {
    return -1;
  }
}

int parse_perms(const char *permissions)
{
  int perms = 0;
  for (int i = 0; i < strlen(permissions); i++)
  {
    perms = perms * 8 + (permissions[i] - '0');
  }

  if (perms > 0777)
  {
    printf("Invalid permissions\n");
    return -1;
  }

  return perms;
}

void flush_buffer(char *buf)
{
  for (int i = 0; i < sizeof(buf); i++)
  {
    buf[i] = '\0';
  }
}
