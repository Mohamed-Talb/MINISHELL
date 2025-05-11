/*
                                      CHDIR FUNCTION
CHDIR FUNCTION: The `chdir` function changes the current working directory of the calling process.

FEATURES:
- Changes the process’s current working directory to the specified path.
- Returns 0 on success and -1 on error (use `perror` for error details).
- Allows programs to navigate the filesystem.

FUNCTION PROTOTYPE:
    int chdir(const char *path);

HOW IT WORKS:
    STEP                        DESCRIPTION
    ------------------------    ------------------------------------------------------------
    Call chdir()                The function changes the working directory to the path specified by `path`.
    Path check                  If `path` is NULL, it changes to the user’s home directory.
    Return value                Returns 0 on success, or -1 on error (use `perror` to print errors).

USAGE SCENARIOS:
- Used to change the directory within scripts or programs.
- Commonly used in shell programs or when running commands in different directories.

COMPILATION:
No special linking required for `chdir`.

*/
#include <stdio.h>
#include <unistd.h>

int main() {
    if (chdir("/bin") == 0) {
        printf("Changed directory successfully.\n");
    } else {
        perror("chdir");
    }
    char *flags[3] = {"ls", "-l", NULL};
    execve("/bin/ls", flags, NULL);
    return 0;
}
