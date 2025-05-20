/*
                                      TCSETATTR AND TCGETATTR FUNCTIONS
TCSETATTR AND TCGETATTR FUNCTIONS: `tcsetattr` and `tcgetattr` are used for controlling terminal input/output settings.

FEATURES:
- `tcgetattr`: Retrieves the current terminal attributes.
- `tcsetattr`: Sets the terminal attributes based on the provided settings.
- Commonly used for changing terminal modes, such as enabling/disabling canonical mode or configuring echo behavior.

FUNCTION PROTOTYPE:
    int tcgetattr(int fd, struct termios *termios_p);
    int tcsetattr(int fd, int optional_actions, const struct termios *termios_p);

HOW IT WORKS:
    STEP                        DESCRIPTION
    ------------------------    ------------------------------------------------------------
    Call tcgetattr()            The function retrieves the terminal settings for the file descriptor `fd`.
    Call tcsetattr()            The function modifies the terminal settings for the given file descriptor.
    Return value                Returns 0 on success, or -1 on failure.

USAGE SCENARIOS:
- Used for modifying terminal behavior, such as disabling input buffering or setting raw mode for serial communication.
- Common in programs that interact with terminals, like text editors or terminal-based applications.

COMPILATION:
No special linking required for `tcsetattr` and `tcgetattr`.
*/
#include <stdio.h>
#include <unistd.h>
#include <termios.h>

int main() {
    struct termios term;
    int fd = fileno(stdout);  // Example: Modifying terminal attributes

    // Get current terminal attributes
    if (tcgetattr(fd, &term) == 0) {
        // Modify terminal settings
        term.c_lflag &= ~ECHO;  // Disable echo
        tcsetattr(fd, TCSANOW, &term);
        printf("Terminal attributes updated.\n");
    } else {
        perror("tcgetattr");
    }

    return 0;
}
