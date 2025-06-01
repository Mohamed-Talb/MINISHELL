/*
                                      TGETNUM FUNCTION
TGETNUM FUNCTION: The `tgetnum` function retrieves a numeric terminal capability from the terminal's capabilities database.

FEATURES:
- Queries a terminal capability that is represented by a number (e.g., number of columns, number of lines).
- Returns a numeric value representing the capability.
- Essential for programs that need to query terminal configurations related to size or other numeric attributes.

FUNCTION PROTOTYPE:
    int tgetnum(const char *id);

HOW IT WORKS:
    STEP                        DESCRIPTION
    ------------------------    ------------------------------------------------------------
    Call tgetnum()              The function retrieves a numeric terminal capability identified by `id`.
    Return value                Returns the numeric value of the capability, or -1 on error.

USAGE SCENARIOS:
- Used in programs that need to retrieve numeric values for terminal settings, such as determining screen size or capabilities.
- Often used in terminal-based applications that adapt to different screen sizes.

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

    // Retrieve the number of columns the terminal can support
    int cols = tgetnum("co");
    if (cols != -1) {
        printf("The terminal supports %d columns.\n", cols);
    } else {
        printf("Failed to retrieve the number of columns.\n");
    }

    return 0;
}
