/*
                                         RL_CLEAR_HISTORY FUNCTION
RL_CLEAR_HISTORY FUNCTION: The `rl_clear_history` function is used to **clear the history list**
maintained by the GNU Readline library. This is helpful if you want to **reset the command history**
during the runtime of a program, typically in command-line interfaces or shells.

FEATURES:
- Clears all entries from the current history list.
- Useful in programs where session-based history is needed.
- Prevents previous input lines from being accessed via arrow keys after clearing.
- Part of the GNU Readline library.

HOW IT WORKS:
    STEP                            DESCRIPTION
    ----------------------------    ----------------------------------------------------------
    User inputs commands            These get stored in the Readline history.
    rl_clear_history() called       All stored history entries are deleted.
    New input starts fresh          History behaves as if no previous input was entered.

EXAMPLE WORKFLOW:

    User types: "ls", "cd ..", "echo Hello"
    History:    [ "ls", "cd ..", "echo Hello" ]
    Call:       rl_clear_history();
    History:    [ ] ← History list is now empty

COMPILATION NOTE:
As with other Readline functions, you need to link the GNU Readline library:

    gcc clear_history_example.c -lreadline -lncurses

*/

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main()
{
    char *line;

    // Read a few lines and store in history
    for (int i = 0; i < 3; i++) {
        line = readline("Enter a command: ");
        if (!line) break;
        add_history(line);
        free(line);
    }

    printf("\nClearing history...\n");
    rl_clear_history();

    // After clearing, this input won't recall previous commands
    line = readline("History cleared. Enter another command: ");
    free(line);

    return 0;
}
