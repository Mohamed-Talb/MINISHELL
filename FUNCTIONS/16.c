/*
                                      CLOSEDIR FUNCTION
CLOSEDIR FUNCTION: The `closedir` function closes a directory stream opened by `opendir`.

FEATURES:
- Closes an open directory stream and releases resources associated with it.
- Used after reading from a directory to free up resources.
- Essential for proper memory management.

FUNCTION PROTOTYPE:
    int closedir(DIR *dirp);

HOW IT WORKS:
    STEP                        DESCRIPTION
    ------------------------    ------------------------------------------------------------
    Call closedir()             The function closes the directory stream, freeing any resources.
    Return value                Returns 0 on success, or -1 if an error occurs.

USAGE SCENARIOS:
- Always called after completing directory operations to prevent resource leaks.
- Important for cleanup in programs that open many directories.

COMPILATION:
No special linking required for `closedir`.

*/
#include <stdio.h>
#include <dirent.h>

int main() {
    DIR *dir = opendir("/home/user");

    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    // Process directory entries here...

    closedir(dir); // Always close the directory when done
    return 0;
}
