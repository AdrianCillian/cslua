# CSLUA: C Shell LUA
"CSLua" is a programming language subset of Lua that combines the features of the C shell (csh) with Lua's syntax and semantics. CSLua provides a set of 100 functions that are specifically designed to simplify system-level programming tasks, such as file management, process handling, and system configuration.

Here are the 100 functions provided by CSLua and their corresponding descriptions:

access() - Determines whether the user has access permission to a file
alarm() - Schedules an alarm signal to occur after a specified time interval
basename() - Returns the base name of a file path
chdir() - Changes the current working directory
chmod() - Changes the permission mode of a file
chroot() - Changes the root directory of a process
clock() - Returns the processor time used by the program
close() - Closes a file descriptor
closedir() - Closes a directory stream
ctime() - Converts a time value to a string
daemon() - Detaches the program from the terminal and runs it in the background
dirname() - Returns the directory name of a file path
dup() - Duplicates a file descriptor
dup2() - Duplicates a file descriptor to a specified descriptor
exec() - Executes a program file
exit() - Terminates the program execution
fcntl() - Performs various file control operations
fdopen() - Associates a file stream with a file descriptor
fgets() - Reads a line from a file stream
fileno() - Returns the file descriptor associated with a file stream
floor() - Rounds a floating-point value down to the nearest integer
fork() - Creates a new process by duplicating the current process
fpathconf() - Returns a configuration value for a file
free() - Frees a memory block allocated by the program
freopen() - Reopens a file stream with a new file name
fstat() - Returns the status of a file
ftell() - Returns the current position of a file stream
fwrite() - Writes data to a file stream
gc() - Performs garbage collection on the Lua heap
getenv() - Returns the value of an environment variable
getgid() - Returns the group ID of the current process
getgroups() - Returns the group IDs of the current user
gethostname() - Returns the host name of the current machine
getlogin() - Returns the login name of the current user
getpgrp() - Returns the process group ID of the current process
getpid() - Returns the process ID of the current process
getppid() - Returns the process ID of the parent process
getuid() - Returns the user ID of the current process
getwd() - Returns the current working directory
gmtime() - Converts a time value to a GMT-based struct
glob() - Searches for files matching a pattern
htons() - Converts a 16-bit integer from host byte order to network byte order
inet_addr() - Converts an IP address string to a binary form
isatty() - Determines whether a file descriptor is associated with a terminal
kill() - Sends a signal to a process
link() - Creates a hard link between two files
listen() - Listens for connections on a socket
localtime() - Converts a time value to a local-time struct
lseek() - Changes the position of a file pointer
lstat() - Returns the status of a file (like stat(), but does not follow symbolic links)
malloc() - Allocates a memory block of a specified size
mkdir() - Creates a new directory
mkfifo() - Creates a new named pipe
mknod() - Creates a special file node
mmap() - Maps a file into memory
mount() - Mounts a file system
nice() - Sets the process priority
open() - Opens a file
opendir() - Opens a directory stream
pclose() - Closes a pipe stream
pipe() - Creates a pipe
popen() - Opens a pipe stream
pread() - Reads data from a file descriptor at a specific offset
pselect() - Waits for events on a set of file descriptors
pthread() - Creates a new thread
putenv() - Sets the value of an environment variable
readdir() - Reads the next directory entry from a directory stream
readlink() - Reads the value of a symbolic link
realpath() - Returns the absolute path of a file
recv() - Receives data from a socket
remove() - Deletes a file
rename() - Renames a file
rewind() - Sets the file position to the beginning of a file
rmdir() - Removes a directory
select() - Waits for events on a set of file descriptors
send() - Sends data over a socket
setbuf() - Sets the buffering mode for a file stream
setgid() - Changes the group ID of the current process
setgroups() - Changes the group IDs of the current user
sethostname() - Changes the host name of the current machine
setlogin() - Changes the login name of the current user
setpgid() - Sets the process group ID of a process
setpriority() - Sets the process priority
setsockopt() - Sets socket options
setuid() - Changes the user ID of a process
shmget() - Allocates shared memory
shmctl() - Controls shared memory
shmread() - Reads shared memory
shmwrite() - Writes to shared memory
sigaction() - Sets the action for a signal
sigemptyset() - Initializes a signal set to be empty
sigfillset() - Initializes a signal set to include all signals
sigprocmask() - Modifies the signal mask of a process
sleep() - Suspends program execution for a specified amount of time
socket() - Creates a new socket
stat() - Returns the status of a file
strerror() - Returns a string describing an error code
symlink() - Creates a symbolic link
umask() - Sets the file mode creation mask
Overall, CSLua provides a powerful set of functions for system-level programming tasks, making it a useful language subset for developers who need to interact with the operating system directly. By combining the syntax and semantics of Lua with the functionality of the C shell, CSLua offers a unique and powerful toolset for programming tasks that require low-level system access.


# SUBSET PROGRAMMING LANGUAGE: SHELLUA

Shellua is a high-level programming language that builds upon the foundation of CSLua to provide a powerful set of tools for developers working on 16-bit, 32-bit, 64-bit, and 86-bit systems. With its rich set of features and intuitive syntax, Shellua enables developers to easily create complex applications and perform high-level processing tasks with ease.

Some of the key features of Shellua include:

Object-oriented programming: Shellua allows developers to create classes, objects, and inheritance relationships, making it easy to write code that is modular and reusable.

Memory management: Shellua provides automatic memory management features that help developers avoid memory leaks and other common programming errors.

High-level data types: Shellua includes built-in support for high-level data types such as lists, dictionaries, and sets, making it easy to work with complex data structures.

File input/output: Shellua includes powerful file input/output capabilities that allow developers to read and write data to files, streams, and other sources.

Networking: Shellua provides built-in support for networking, allowing developers to easily create applications that communicate over the internet or other networks.

Graphical user interfaces: Shellua includes libraries for creating graphical user interfaces (GUIs), making it easy to create user-friendly applications.

Some of the most commonly used functions in Shellua include:

print() - Prints a message to the console or terminal.

input() - Reads input from the user.

open() - Opens a file for reading or writing.

read() - Reads data from a file or stream.

write() - Writes data to a file or stream.

close() - Closes a file or stream.

connect() - Establishes a network connection.

send() - Sends data over a network connection.

receive() - Receives data over a network connection.

GUI functions - Functions for creating windows, buttons, menus, and other GUI elements.

Overall, Shellua is a powerful and versatile programming language that offers a high-level programming experience for developers working on a wide range of systems. With its intuitive syntax, rich feature set, and robust libraries, Shellua is an excellent choice for building complex applications and performing high-level processing tasks.
