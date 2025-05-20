/*
                                      LSTAT FUNCTION
LSTAT FUNCTION: The `lstat` function works like `stat`, but does not follow symbolic links. Instead, it returns information about the symlink itself.

FEATURES:
- Similar to `stat`, but does not follow symbolic links.
- Returns metadata about the symlink rather than the target file.
- Useful for checking symbolic link properties without dereferencing them.

FUNCTION PROTOTYPE:
    int lstat(const char *path, struct stat *buf);

HOW IT WORKS:
    STEP                        DESCRIPTION
    ------------------------    ------------------------------------------------------------
    Call lstat()                The function retrieves information about a symbolic link specified by `path`.
    Populate `struct stat`     The `buf` structure holds metadata about the symlink itself.
    Return value                Returns 0 on success, or -1 on error.

USAGE SCENARIOS:
- Used when the program needs to retrieve information about symbolic links without following them.
- Useful in file system utilities that need to handle symlinks differently.

COMPILATION:
No special linking required for `lstat`.

*/
#include <stdio.h>
#include <sys/stat.h>

int main() {
    struct stat buf;

    if (lstat("symlink", &buf) == 0) {
        printf("Symbolic link size: %ld bytes\n", buf.st_size);
    } else {
        perror("lstat");
    }

    return 0;
}
