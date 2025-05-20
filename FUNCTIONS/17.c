/*
                                      ISATTY FUNCTION
ISATTY FUNCTION: The `isatty` function checks whether a given file descriptor refers to a terminal.

FEATURES:
- Returns true if the file descriptor refers to a terminal.
- Used to check if the output is directed to a terminal, commonly for formatting terminal-specific output.
- Essential for terminal-related operations in command-line applications.

FUNCTION PROTOTYPE:
    int isatty(int fd);

HOW IT WORKS:
    STEP                        DESCRIPTION
    ------------------------    ------------------------------------------------------------
    Call isatty()               The function checks if the file descriptor `fd` refers to a terminal.
    Return value                Returns 1 if the file descriptor refers to a terminal, or 0 if not.

USAGE SCENARIOS:
- Used in command-line tools to conditionally format output, such as colored text.
- Essential in terminal-based programs to verify if the input/output is interactive.

COMPILATION:
No special linking required for `isatty`.
*/
#include <stdio.h>
#include <unistd.h>

int main() {
    int fd = fileno(stdout); // Example: Checking if stdout is a terminal

    if (isatty(fd)) {
        printf("The output is a terminal.\n");
    } else {
        printf("The output is not a terminal.\n");
    }

    return 0;
}
