/*
                                      READDIR FUNCTION
READDIR FUNCTION: The `readdir` function reads the next entry from a directory stream opened by `opendir`.

FEATURES:
- Reads the next entry in the directory stream.
- Returns a pointer to a `struct dirent` containing the entry's name and type.
- Returns `NULL` when the end of the directory is reached.

FUNCTION PROTOTYPE:
    struct dirent *readdir(DIR *dirp);

HOW IT WORKS:
    STEP                        DESCRIPTION
    ------------------------    ------------------------------------------------------------
    Call readdir()              The function reads the next entry in the opened directory stream.
    Return value                Returns a pointer to a `struct dirent` containing the entry's name, or `NULL` if the end is reached.

USAGE SCENARIOS:
- Used for directory traversal, typically in file listing or directory search programs.
- Common in tools that manipulate file systems or search for specific files.

COMPILATION:
No special linking required for `readdir`.

*/
#include <stdio.h>
#include <dirent.h>

int main() {
    DIR *dir = opendir("/home/user");
    struct dirent *entry;

    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        printf("Found: %s\n", entry->d_name);
    }

    closedir(dir); // Close the directory when done
    return 0;
}
