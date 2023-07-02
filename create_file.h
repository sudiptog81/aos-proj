#ifndef SYSCALL_CREATE_FILE
#define SYSCALL_CREATE_FILE

/**
 * @file create_file.h
 * @author Sudipto Ghosh
 * @brief Module to create a file using system calls
 */

/**
 * @brief Creates a regular file or a named pipe using the `creat()` or `mknod()`
 * system call.
 *
 * It also sets the file permissions to `perms` by using the mode bits supplied.
 *
 * This function is invoked by the `create` command.
 *
 * In case the target file already exists, the user is prompted for confirmation
 * and needs to pass the `-f` flag to force this operation.
 *
 * @param path the absolute or relative path of the file to create with filename
 * @param perms the permissions to set for the file using mode bits
 * @param file_type flag to denote regular file (0) or named pipe (-1)
 * @param force_flag flag to force create if the file exists
 * @return 0 on success, -1 on failure
 */
int create_file(const char *, const int, const int, const int);

#endif
