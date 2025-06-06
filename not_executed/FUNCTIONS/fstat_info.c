/*
                                      FSTAT FUNCTION
FSTAT FUNCTION: The `fstat` function retrieves information about a file using its file descriptor.

FEATURES:
- Similar to `stat`, but takes a file descriptor instead of a path.
- Can be used after opening a file using `open()` or other file-related functions.
- Provides the same information as `stat`, but using a file descriptor.

FUNCTION PROTOTYPE:
    int fstat(int fd, struct stat *buf);

HOW IT WORKS:
    STEP                        DESCRIPTION
    ------------------------    ------------------------------------------------------------
    Call fstat()                The function retrieves information about the file using the file descriptor `fd`.
    Populate `struct stat`     The `buf` structure holds metadata about the file.
    Return value                Returns 0 on success, or -1 on error.

USAGE SCENARIOS:
- Used when working with file descriptors, often after opening a file.
- Common in file manipulation utilities, network applications, and system-level programming.

COMPILATION:
No special linking required for `fstat`.

*/
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    struct stat buf;
    int fd = open("example.txt", O_RDONLY);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    if (fstat(fd, &buf) == 0) {
        printf("File size: %ld bytes\n", buf.st_size);
    } else {
        perror("fstat");
    }

    close(fd);
    return 0;
}
