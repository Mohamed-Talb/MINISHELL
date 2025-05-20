/*
                                           READLINE FUNCTION
READLINE FUNCTION: The `readline` function is used to read an entire line of text input
from the user (or another input source) until a newline (`\n`) or EOF (End Of File) is reached.
It dynamically allocates memory for the input line and returns it as a string.

FEATURES:
- Dynamically handles input of any size.
- Returns a `char *` pointing to a newly allocated buffer.
- Commonly used in command-line programs, especially in shell environments.
- Comes from the GNU Readline library (not part of standard C).

HOW IT WORKS:
    STEP                        DESCRIPTION
    ------------------------    --------------------------------------------------------
    Allocate buffer             Starts with an initial memory buffer (e.g., 128 bytes).
    Read character-by-character Reads input until newline or EOF.
    Resize buffer if needed     Uses realloc if buffer size exceeded.
    End on newline or EOF       Terminates reading and appends '\0'.
    Return input string         Returns the dynamically allocated string.

EXAMPLE WORKFLOW:

    User types: hello world<Enter>
    readline stores: ['h','e','l','l','o',' ','w','o','r','l','d','\0']
                     ^ Buffer returned to the program.

COMPILATION NOTE:
To compile this program, you must link the GNU Readline library using the -lreadline flag.
You may also need to link with -lncurses depending on your system.

    gcc readline_example.c -lreadline -lncurses

*/

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

int main()
{
    char *line;

    // Prompt user for input
    line = readline("Enter a line: ");

    // If line is NULL, EOF was received
    if (!line) {
        printf("No input received or EOF encountered.\n");
        return 1;
    }

    // Print the line read
    printf("You entered: %s\n", line);

    // Free the memory allocated by readline
    free(line);

    return 0;
}
