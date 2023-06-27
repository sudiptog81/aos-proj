#ifndef SYSCALL_STAT_FILE
#define SYSCALL_STAT_FILE

/**
 * @file stat_file.h
 * @author Sudipto Ghosh
 * @brief Module to get statistical information about a file
 */

/**
 * @brief Queries information about a file using `stat()` system call.
 *
 * It prints the following information about the file to the console:
 * - File type
 * - Device ID
 * - Major device ID
 * - Minor device ID
 * - File size (in bytes)
 * - Blocks allocated
 * - Filesystem block size
 * - Inode
 * - Links
 * - Owner permissions
 * - Group permissions
 * - Other permissions
 * - Owner user and UID
 * - Owner group and GID
 * - Last accessed
 * - Last modified
 * - Last changed
 *
 * This function is invoked by the `info` command.
 *
 * @param path the absolute or relative path of the file
 * @return 0 on success, -1 on failure
 */
int stat_file(const char *);

#endif
