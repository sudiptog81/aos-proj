#ifndef SYSCALL_READ_FILE
#define SYSCALL_READ_FILE

/**
 * @file read_file.h
 * @author Sudipto Ghosh
 * @brief Module to read a file using system calls
 */

/**
 * @brief Reads a regular file using the `read()` system call and writes the
 * content to `stdout`.
 *
 * This function is invoked by the `read` command.
 *
 * @param path the absolute or relative path to the file to be read
 * @param offset the offset from the beginning of the file
 * @param nBytes the number of bytes to read from the file, -1 to read the entire file
 * @return nBytes denoting number of bytes read from file, -1 on failure
 */
int read_file(const char *, const int, const int);

#endif
