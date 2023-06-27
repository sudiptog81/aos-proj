#include <fcntl.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include "helpers.h"

int stat_file(const char *path)
{
  // get file information and store in _stat
  struct stat _stat;
  int s = stat(path, &_stat);

  if (s < 0)
  {
    printf("Error getting file information\n");
    return -1;
  }

  // file information
  printf("File: %s\n", path);

  // file type
  printf("Type: ");
  switch (_stat.st_mode & __S_IFMT)
  {
  case __S_IFBLK:
    printf("block device\n");
    break;
  case __S_IFCHR:
    printf("character device\n");
    break;
  case __S_IFDIR:
    printf("directory\n");
    break;
  case __S_IFIFO:
    printf("FIFO/pipe\n");
    break;
  case __S_IFLNK:
    printf("symlink\n");
    break;
  case __S_IFREG:
    printf("regular file\n");
    break;
  case __S_IFSOCK:
    printf("socket\n");
    break;
  default:
    printf("unknown?\n");
    break;
  }

  // device information
  printf("Device: %ld\n", _stat.st_dev);
  printf("Major Device: %ld\n", (long)major(_stat.st_dev));
  printf("Minor Device: %ld\n", (long)minor(_stat.st_dev));

  // statistical information
  printf("Size: %ld\n", _stat.st_size);
  printf("Blocks Allocated (in 512B units): %ld\n", _stat.st_blocks);
  printf("Filesystem Block Size: %ld\n", _stat.st_blksize);
  printf("Inode: %ld\n", _stat.st_ino);
  printf("Links: %ld\n", _stat.st_nlink);

  // permissions
  printf("Owner Permissions: ");
  printf((_stat.st_mode & S_IRUSR) ? "r" : "-");
  printf((_stat.st_mode & S_IWUSR) ? "w" : "-");
  printf((_stat.st_mode & S_IXUSR) ? "x" : "-");
  printf("\n");

  printf("Group Permissions: ");
  printf((_stat.st_mode & S_IRGRP) ? "r" : "-");
  printf((_stat.st_mode & S_IWGRP) ? "w" : "-");
  printf((_stat.st_mode & S_IXGRP) ? "x" : "-");
  printf("\n");

  printf("Other Permissions: ");
  printf((_stat.st_mode & S_IROTH) ? "r" : "-");
  printf((_stat.st_mode & S_IWOTH) ? "w" : "-");
  printf((_stat.st_mode & S_IXOTH) ? "x" : "-");
  printf("\n");

  // owner and group information
  printf("Owner User: %s (UID: %d)\n", getpwuid(_stat.st_uid)->pw_name, _stat.st_uid);
  printf("Owner Group: %s  (GID: %d)\n", getgrgid(_stat.st_gid)->gr_name, _stat.st_gid);

  // timestamps
  printf("Last Accessed: %s", ctime(&_stat.st_atime));
  printf("Last Modified: %s", ctime(&_stat.st_mtime));
  printf("Last Changed: %s", ctime(&_stat.st_ctime));

  return 0;
}
