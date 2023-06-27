#ifndef SYSCALL_UNNAMED_PIPE
#define SYSCALL_UNNAMED_PIPE

/**
 * @file unnamed_pipe.h
 * @author Sudipto Ghosh
 * @brief Module to demonstrate use of unnamed pipes for message passing
 */

/**
 * @brief Uses unnamed pipes for message passing between a parent and  a child process.
 *
 * It creates a pipe using the `pipe()` system call and forks a child process. The parent
 * process writes to the pipe and the child process reads from it.
 *
 * The user is prompted to enter a message to write to the pipe. The user can exit the
 * program by entering `:q` as the message.
 *
 * This function is invoked by the `pipe` command.
 *
 * @return 0 on success, -1 on failure
 */
int unnamed_pipe(void);

#endif
