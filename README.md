# System Calls CLI

This is a command-line program that can be used to demonstrate system calls in UNIX. It is written in C and uses the GNU C Library and the POSIX API.

This project was done as a part of the Advanced Operating Systems (MCSC202) course at the University of Delhi.

Function references are available online at <https://syscalls-cli.ghosh.pro/html/files.html>.

## Features

This program supports the following features as of now:

- creating a file/named pipe with permissions as given by user
- reading from a file and printing the contents to `stdout`
- writing to a file from `stdin`
- displaying statistical information about a file
- copying the contents of one file to another using an unnamed pipe
- using a named pipe to communicate between two processes

_Note_: The reading and writing operations also support offsets and number of bytes to be read or written.

## Commands

The various commands supported by this program can be listed by running the program without any arguments.

```bash
$ ./main
Usage: ./main [command] [options...] [file1] [file2...]
Commands:
  create: create a file or a named pipe
  read: read a file and print to stdout
  write: write to a file
  copy: copy a file using an unnamed pipe
  info: information about a file
  pipe: create a pipe and simulate communication between processes

```

## Usage

Each command has its own set of options and arguments. The usage of each commmand can be known by executing `./main [command]`. The details of each command are given below.

### Creating Files

The `create` command should be used to create a file or a named pipe. The permissions of the file or named pipe have to be specified after the path as an octal number. The `-p` flag can be used to create a named pipe.

#### Example: Creating a Regular File

```bash
$ ./main create file.txt 0644
```

#### Example: Creating a Named Pipe

```bash
$ ./main create -p pipe 0666
```

_Note_: In case the file or named pipe already exists, the program will exit with an error asking the user to pass the `-f` flag if they really want to do so.

### Reading Files

The `read` command should be used to read a file and print its contents to `stdout` i.e. the console. The `-o` flag can be used to specify the offset from which the file should be read. The `-n` flag can be used to specify the number of bytes to be read from the file. If the `-n` flag is not used, the entire file will be read. If the `-o` flag is not used, the file will be read from the beginning.

#### Example: Reading a File

```bash
$ ./main read file.txt
lorem ipsum dolor amet
```

#### Example: Reading a File (With Offset and Number of Bytes)

```bash
$ ./main read file.txt -o 6 -n 5
ipsum
```

### Writing to Files

The `write` command should be used to write to a file from `stdin` - the console or a shell pipe. The `-o` flag can be used to specify the offset from which the file should be written to. The `-n` flag can be used to specify the number of bytes to be written to the file. If the `-n` flag is not used, the entire file will be written to. If the `-o` flag is not used, the file will be written to from the beginning.

The user is prompted with a message to enter the text to be written to the file. The user can enter the contents of the file. To end the input, the user has to type `:w` followed by the `Enter` key.

In order to append to a file, the `-a` flag can be used. This will append the contents to the end of the file. This can also be used with the `-o` flag to append to a file from a specific offset after the end of the file. This option should not be used with the `-f` flag.

#### Example: Writing to a File

```bash
$ ./main write file.txt
type :w to exit
---------------
lorem ipsum
:w
```

#### Example: Appending to a Fileipsum

```bash
$ ./main write -a file.txt
type :w to exit
---------------
dolor amet
:w
```

### Copying Files

The `copy` command should be used to copy the contents of one file to another using an unnamed pipe. If the destination file exists, the program will force the user to pass the `-f` flag to overwrite it.

#### Example: Copying a File

```bash
$ ./main copy file.txt file2.txt
Copied file.txt to file2.txt...
```

### File Information

The `info` command should be used to display statistical information about a file. The information displayed includes the file type, permissions, number of hard links, owner, group, size, block size, number of blocks, last access time, last modification time, and last status change time.

#### Example: Displaying File Information (Regular File)

```bash
$ ./main info a.txt
File: a.txt
Type: regular file
Device: 66311
Major Device: 259
Minor Device: 7
Size: 15
Blocks Allocated (in 512B units): 8
Filesystem Block Size: 4096
Inode: 15994677
Links: 1
Owner Permissions: rwx
Group Permissions: rwx
Other Permissions: rwx
Owner User: sudipto (UID: 1000)
Owner Group: sudipto  (GID: 1001)
Last Accessed: Tue Jun 27 11:16:42 2023
Last Modified: Tue Jun 27 15:04:14 2023
Last Changed: Tue Jun 27 15:04:14 2023
```

#### Example: Displaying File Information (Special File)

```bash
$ ./main info /dev/nvme0n1p1
File: /dev/nvme0n1p1
Type: block device
Device: 5
Major: 0
Minor: 5
Size: 0
Blocks Allocated (in 512B units): 0
Filesystem Block Size: 4096
Inode: 477
Links: 1
Owner Permissions: rw-
Group Permissions: rw-
Other Permissions: ---
Owner User: root (UID: 0)
Owner Group: disk  (GID: 995)
Last Accessed: Sun Jun 25 08:18:52 2023
Last Modified: Sun Jun 25 08:18:06 2023
Last Changed: Sun Jun 25 08:18:06 2023
```

### Pipes

The `pipe` command should be used to create a pipe and simulate communication between two processes. This program can demonstrate this using both unnamed as well as named pipes.

#### Unnamed Pipes

If used with `-u` flag, it creates an unnamed pipe. The user is prompted with a message to enter the text to be written to the pipe. The user can enter the contents of the pipe. To end the input, the user has to type `:q` followed by the `Enter` key. Internally, the program forks a child process and the parent process writes to the pipe and the child process reads it from the pipe and prints the contents to `stdout`.

```bash
$ ./main pipe -u
type :q to exit
----------------
Message: Hello
Received from Parent: Hello
Message: :q
Received Bye from Parent...
```

#### Named Pipes

If a path is specified, it uses a named pipe in the mode (reader or writer) specified by the argument after the path of the pipe. The user is prompted with a message to enter the text to be written to the pipe. The user can enter some text and press `Enter` to send the message. To end the input, the user has to type `:q` followed by the `Enter` key. If the pipe already exists, the program will force the user to pass the `-f` flag to overwrite it, otherwise, it will attempt to use the existing pipe.

Multiple instances of the program have to be run on different terminals to demonstrate communication between processes. In case multiple readers are waiting for a writer, the first reader to read from the pipe will receive the message and the rest will receive an empty string. This is because the message is removed from the pipe after it is read. Which reader receives the message is determined by the operating system scheduler.

```bash
# writer process
$ ./main pipe pipe w        
type :q to exit
----------------
Message: Hello World
Message: :q 

# reader process
$ ./main pipe pipe r
Waiting for writer...
Received: Hello World
Received Bye...
```

## Author

Sudipto Ghosh (51)<br />
Department of Computer Science<br />
University of Delhi
