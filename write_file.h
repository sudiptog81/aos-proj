#ifndef SYSCALL_WRITE_FILE
#define SYSCALL_WRITE_FILE

/**
 * @file write_file.h
 * @author Sudipto Ghosh
 * @brief Module to write to a file using system calls
 */

/**
 * @brief Writes to a regular file from `stdin` using the `write()` system call.
 *
 * If used with the append_flag set, it appends to the file instead of overwriting it.
 * The offset and nBytes can be used to write a specified number of bytes to a specific
 * location in the file.
 *
 * It uses `getline()` to read ther user input from `stdin` and writes to the file
 * using `write()` system call. The user has to enter `:w` to stop writing
 * to the file and close its file descriptor.
 *
 * This function is invoked by the `write` command.
 *
 * In case the file already exists, the user is prompted for confirmation and needs to
 * pass the `-f` flag to force this operation. It either truncates the file or creates
 * the file with the default permissions of `0644`.
 *
 * @param path the absolute or relative path to the file to be written
 * @param offset the offset from the beginning of the file to start writing
 * @param nBytes the number of bytes to write to the file, -1 to read the entire file
 * @param append_flag flag to append to the file instead of overwriting it
 * @param force_flag flag to force truncate first if the file exists
 * @return 0 on success, -1 on failure
 */
int write_file(const char *, const int, const int, const int, const int);

#endif
