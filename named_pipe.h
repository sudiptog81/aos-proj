#ifndef SYSCALL_NAMED_PIPE
#define SYSCALL_NAMED_PIPE

/**
 * @file named_pipe.h
 * @author Sudipto Ghosh
 * @brief Module to demonstrate use of named pipes for message passing
 */

/**
 * @brief Uses named pipes for message passing between reader and writer processes.
 *
 * If invoked in write mode, the program will create a named pipe at the specified
 * path if it doesn't exist and write to it. If invoked in read mode, the program
 * will wait for a writer to write to the named pipe and then read from it.
 *
 * In write mode, the user is prompted to enter a message to write to the named pipe.
 * The user can exit the program by entering `:q` as the message.
 *
 * In read mode, the program will wait for a writer to write to the named pipe and
 * then read from it. The process will exit when it receives `:q` from the writer.
 *
 * @param path the path to the named pipe
 * @param read_flag  0 for write mode, 1 for read mode
 * @return 0 on success, -1 on failure
 */
int named_pipe(const char *, const int);

#endif
