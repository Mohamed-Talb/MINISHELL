/*
                                      ADD_HISTORY FUNCTION
ADD_HISTORY FUNCTION: The `add_history` function is part of the GNU Readline library. It is used to
add a string to the **history list** of commands or input lines. The history is a collection of previously 
entered input that can be accessed or recalled for convenience, typically using the Up and Down arrow keys.

FEATURES:
- Adds the input line to the history list.
- Makes the input available for future recall or editing.
- Stores the history in memory or in a file, depending on the configuration.
- Typically used in command-line programs to allow users to recall previous commands.

FUNCTION PROTOTYPE:
    void add_history(const char *line);

HOW IT WORKS:
    STEP                        DESCRIPTION
    ------------------------    ------------------------------------------------------------
    Input received              User types a line of input (e.g., in a shell or prompt).
    Call add_history()          Adds the input line to the history list.
    History accessible          The input is now part of the history and can be recalled.

USAGE SCENARIOS:
- After each input command, to add it to the history.
- For shell-like applications where users can recall past commands.
- In interactive programs to remember user input across sessions.
- Can be used to enhance usability by allowing navigation through past inputs.

COMPILATION:
To compile programs that use add_history, link with Readline and Ncurses:

    gcc your_file.c -lreadline -lncurses

*/

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main()
{
    char *line = readline("Input a command: ");

    if (!line)
        return 1;

    if (strcmp(line, "exit") == 0)
    {
        free(line);
        return 0;
    }

    // Add the line to the history list
    add_history(line);

    printf("You entered: %s\n", line);
    free(line);
    return 0;
}
