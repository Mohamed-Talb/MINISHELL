/*
                                      RL_REDISPLAY FUNCTION
RL_REDISPLAY FUNCTION: The rl_redisplay function is part of the GNU Readline library. It is used to
update and refresh the terminal display of the current input line being edited. This is particularly
important after modifying the input buffer using functions like rl_replace_line.

FEATURES:
- Re-renders the current input line to the terminal.
- Does not modify the buffer, only redraws it.
- Useful after programmatically changing the input line.
- Helps keep the UI in sync when modifying Readline's internal buffer.

FUNCTION PROTOTYPE:
    void rl_redisplay(void);

HOW IT WORKS:
    STEP                        DESCRIPTION
    ------------------------    ------------------------------------------------------------
    Modify input buffer         Example: with rl_replace_line(), the buffer is changed
    Call rl_redisplay()         Forces Readline to redraw the line on the terminal
    Terminal updates            The user sees the new version of the line

USAGE SCENARIOS:
- After replacing input via rl_replace_line.
- When auto-filling or auto-correcting a command.
- After clearing or resetting input.
- To redraw after terminal resize or UI glitch.

COMPILATION:
To compile programs that use rl_redisplay, link with Readline and Ncurses:

    gcc your_file.c -lreadline -lncurses

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

int main()
{
    char *line = readline("Input something: ");

    if (!line)
        return 1;

    if (strcmp(line, "clear") == 0)
    {
        rl_replace_line("", 1);     // Clear input line
        rl_redisplay();             // Redraw the empty line
        printf("\nLine was cleared.\n");
    }
    else
    {
        printf("You typed: %s\n", line);
    }

    free(line);
    return 0;
}
