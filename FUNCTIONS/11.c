/*
                                      STAT FUNCTION
STAT FUNCTION: The `stat` function retrieves detailed information about a file or directory.

FEATURES:
- Provides metadata about a file or directory, such as size, permissions, and timestamps.
- Returns a `struct stat` that holds the file's information.
- Commonly used to check file attributes before performing actions like reading or writing.

FUNCTION PROTOTYPE:
    int stat(const char *path, struct stat *buf);

HOW IT WORKS:
    STEP                        DESCRIPTION
    ------------------------    ------------------------------------------------------------
    Call stat()                 The function retrieves metadata about the file specified by `path`.
    Populate `struct stat`     Information like file size, ownership, and timestamps is stored in `buf`.
    Return value                Returns 0 on success, or -1 on error.

USAGE SCENARIOS:
- Used to gather information about files or directories before manipulating them.
- Often used in file systems, backups, and utilities that need to inspect files.

COMPILATION:
No special linking required for `stat`.

*/
#include <stdio.h>
#include <sys/stat.h>

int main() {
    struct stat buf;

    if (stat("example.txt", &buf) == 0) {
        printf("File size: %ld bytes\n", buf.st_size);
    } else {
        perror("stat");
    }

    return 0;
}
