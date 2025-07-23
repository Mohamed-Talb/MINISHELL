#include "../minishell.h"

int signal_state(int state)
{
    static int value;
    if(state != -1)
        value = state;
    return value;
}

void hanlder(int sig)
{
    (void)sig;
    if (signal_state(-1) == 0)
    {
        write(1, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
    else if (signal_state(-1) == 1)
    {
        write(1, "\n", 1);
        exit(130);
    }
}

void signals()
{
    signal(SIGINT, hanlder);
    signal(SIGQUIT, SIG_IGN);
}
