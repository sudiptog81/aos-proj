#ifndef SYSCALL_READ_FILE
#define SYSCALL_READ_FILE

/**
 * @file read_file.h
 * @author Sudipto Ghosh
 * @brief Module to read a file using system calls
 */

/**
 * @brief Reads a regular file using the `read()` system call and writes the content
 *  to `stdout`.
 *
 * Usage: `read_file("/tmp/passwd");`
 *
 * @param path the absolute or relative path to the file to be read
 * @return nBytes denoting number of bytes read from file, -1 on failure
 */
int read_file(const char *);

#endif
