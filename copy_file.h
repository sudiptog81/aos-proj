#ifndef SYSCALL_COPY_FILE
#define SYSCALL_COPY_FILE

/**
 * @file copy_file.h
 * @author Sudipto Ghosh
 * @brief Module to copy a file using system calls
 */

/**
 * @brief Copies a regular file using the `read()` and `write()` system calls.
 *
 * It copies the content of the source file specified by `src` to the target
 * specified by the `dest` parameter.
 *
 * Usage: `copy_file("/tmp/passwd", "/tmp/passwd.oldbak", 0);`
 *
 * In case the target file already exists,
 * the user is prompted for confirmation and needs to pass the `-f` flag to
 * force this operation.
 *
 * @param src the absolute or relative path to the source file
 * @param dest the absolute or relative path to the destination file
 * @param force_flag flag to force overwrite if the destination file exists
 * @return 0 on success, -1 on failure
 */
int copy_file(const char *, const char *, const int);

#endif
