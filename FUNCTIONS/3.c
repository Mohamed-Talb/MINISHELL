/*
                                        RL_ON_NEW_LINE FUNCTION
RL_ON_NEW_LINE FUNCTION: The `rl_on_new_line` function is a utility provided by the **GNU Readline library**
that tells Readline that the cursor is now on a new line and it's safe to redisplay the prompt and user input.
It is typically used when managing input manually (e.g., when printing output during input).

FEATURES:
- Tells Readline that the internal cursor has moved to a new line.
- Prevents Readline from overwriting output or mixing text.
- Often used before `rl_redisplay()` when updating the screen.

WHY USE IT:
In situations where your program outputs text *while the user is typing*, you might mess up the input line.
`rl_on_new_line()` followed by `rl_redisplay()` ensures the prompt and user input appear correctly after output.

HOW IT WORKS:
    STEP                        DESCRIPTION
    ------------------------    ---------------------------------------------------------------
    Program outputs something   Text is printed while user is typing.
    rl_on_new_line()            Notifies Readline that a new line should begin.
    rl_redisplay()              Redraws the prompt and current input cleanly.

COMPILATION NOTE:
To compile code using `rl_on_new_line`, you need to link with GNU Readline and Ncurses:

    gcc on_new_line_example.c -lreadline -lncurses

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

int main()
{
    char *input;

    // Initial prompt
    input = readline("Type something: ");
    
    // Simulate output during input (like logging or async messages)
    printf("\n[Background] Message arrived!\n");

    // Tell Readline to prepare for redisplaying input
    rl_on_new_line();
    rl_redisplay();

    free(input);
    return 0;
}
