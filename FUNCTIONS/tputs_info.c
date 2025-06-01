/*
                                      TPUTS FUNCTION
TPUTS FUNCTION: The `tputs` function outputs a string to the terminal, handling terminal control sequences.

FEATURES:
- Sends terminal control strings (such as cursor movement or text formatting) to the terminal.
- Handles the required formatting for the terminal's capabilities, ensuring the sequence is correctly interpreted.
- Allows terminal manipulation in a platform-independent way.

FUNCTION PROTOTYPE:
    int tputs(const char *str, int affcnt, int (*putc)(int));

HOW IT WORKS:
    STEP                        DESCRIPTION
    ------------------------    ------------------------------------------------------------
    Call tputs()                The function sends the terminal control string `str` to the terminal, calling `putc` to output it.
    Return value                Returns the result of the `putc` function, or `-1` on error.

USAGE SCENARIOS:
- Used in terminal-based programs for outputting control sequences, such as moving the cursor or changing text attributes.
- Common in text editors and other terminal applications that need to interact with the terminal.

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

    // Generate cursor movement string
    char *move_str = tgoto(tgetstr("cm", NULL), 10, 5);

    // Output the string to the terminal using tputs
    tputs(move_str, 1, putchar);

    return 0;
}
