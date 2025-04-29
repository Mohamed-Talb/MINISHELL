/*
                                      GETCWD FUNCTION
GETCWD FUNCTION: The `getcwd` function retrieves the current working directory of the calling process.

FEATURES:
- Returns the current working directory as a string.
- Can be used to display or manipulate the process’s working directory.
- Returns NULL if the buffer is too small or if an error occurs.

FUNCTION PROTOTYPE:
    char *getcwd(char *buf, size_t size);

HOW IT WORKS:
    STEP                        DESCRIPTION
    ------------------------    ------------------------------------------------------------
    Allocate buffer             A buffer is provided where the current working directory will be stored.
    Retrieve current directory  The function gets the current working directory.
    Return value                Returns the current directory on success, or NULL if there is an error.

USAGE SCENARIOS:
- Useful when the program needs to display or verify the current working directory.
- Commonly used in command-line tools and shell programs.

COMPILATION:
No special linking required for `getcwd`.

*/
#include <stdio.h>
#include <unistd.h>

int main() {
    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working directory: %s\n", cwd);
    } else {
        perror("getcwd");
    }

    return 0;
}
