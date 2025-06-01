/*
                                      TGETFLAG FUNCTION
TGETFLAG FUNCTION: The `tgetflag` function retrieves a boolean terminal capability from the terminal's capabilities database.

FEATURES:
- Queries a terminal capability that is represented as a boolean value (e.g., whether the terminal supports colors, cursor movement).
- Useful for checking if a terminal supports specific features or capabilities.
- Returns 1 if the capability is present, 0 if it is not, and -1 on error.

FUNCTION PROTOTYPE:
    int tgetflag(const char *id);

HOW IT WORKS:
    STEP                        DESCRIPTION
    ------------------------    ------------------------------------------------------------
    Call tgetflag()             The function retrieves a boolean terminal capability identified by `id`.
    Return value                Returns 1 if the capability is present, 0 if not, or -1 on error.

USAGE SCENARIOS:
- Used to check if a terminal supports specific features, such as color output, in programs like terminal-based text editors or utilities.
- Frequently used in conjunction with other terminal control functions for configuring terminal behavior.

COMPILATION:
Requires linking with the `termcap` or `ncurses` library.
*/
#include <stdio.h>
#include <termcap.h>

int main() {
    char *term = getenv("TERM");
    char buffer[2048];
    char *bp = buffer;

    // Load terminal capabilities
    tgetent(bp, term);

    // Check if the terminal supports the "co" capability (number of columns)
    int has_color = tgetflag("co");
    if (has_color == 1) {
        printf("The terminal supports colors.\n");
    } else {
        printf("The terminal does not support colors.\n");
    }

    return 0;
}
