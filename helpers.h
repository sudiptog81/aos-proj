#ifndef HELPERS_AOS
#define HELPERS_AOS

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFSIZE 1024

/**
 * @file helpers.h
 * @author Sudipto Ghosh
 * @brief Module containing helper functions for the program
 */

/**
 * @brief Parses a command string and returns the corresponding command code
 *      or -1 if the command is invalid.
 * @param command string to parse
 * @return command code or -1 if invalid
 */
int parse_command(const char *);

/**
 * @brief Parses a permissions string and returns the corresponding permissions
 *      or -1 if the permissions are invalid.
 * @param perms string to parse
 * @return permission mode bits or -1 if invalid
 */
int parse_perms(const char *);

/**
 * @brief Flushes the buffer by filling null values in it.
 * @param buffer buffer to flush
 */
void flush_buffer(char *);

#endif
