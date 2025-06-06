/*
                                      TTYNAME FUNCTION
TTYNAME FUNCTION: The `ttyname` function returns the name of the terminal associated with a file descriptor.

FEATURES:
- Retrieves the name of the terminal (e.g., `/dev/tty1`) associated with the given file descriptor.
- Useful for identifying the terminal connected to a process.
- Returns a string representing the terminal's device path.

FUNCTION PROTOTYPE:
    char *ttyname(int fd);

HOW IT WORKS:
    STEP                        DESCRIPTION
    ------------------------    ------------------------------------------------------------
    Call ttyname()              The function retrieves the terminal name associated with the given file descriptor.
    Return value                Returns the terminal name on success, or `NULL` if there is no terminal.

USAGE SCENARIOS:
- Used in programs that need to identify or log the terminal from which input/output occurs.
- Common in terminal management utilities.

COMPILATION:
No special linking required for `ttyname`.
*/
#include <stdio.h>
#include <unistd.h>

int main() {
    int fd = fileno(stdout); // Example: Getting the terminal name associated with stdout

    char *terminal_name = ttyname(fd);
    if (terminal_name) {
        printf("The terminal name is: %s\n", terminal_name);
    } else {
        printf("No terminal associated with the file descriptor.\n");
    }

    return 0;
}
