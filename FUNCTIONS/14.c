/*
                                      OPENDIR FUNCTION
OPENDIR FUNCTION: The `opendir` function opens a directory stream for reading directory entries.

FEATURES:
- Used to open a directory for reading.
- Returns a pointer to a `DIR` structure, which can be used by `readdir` to read directory entries.
- Typically used for directory traversal.

FUNCTION PROTOTYPE:
    DIR *opendir(const char *dirname);

HOW IT WORKS:
    STEP                        DESCRIPTION
    ------------------------    ------------------------------------------------------------
    Call opendir()              The function opens the directory specified by `dirname`.
    Return value                Returns a pointer to a `DIR` structure on success, or `NULL` if an error occurs.

USAGE SCENARIOS:
- Commonly used in file system utilities to open directories for reading.
- Essential for iterating over files and directories.

COMPILATION:
No special linking required for `opendir`.

*/
#include <stdio.h>
#include <dirent.h>

int main() {
    DIR *dir = opendir("/home/user");

    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    // Read and process directory entries here...

    closedir(dir); // Always close the directory when done
    return 0;
}
