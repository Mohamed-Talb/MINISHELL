// int signal_state(int state)
// {
//     static int value;
//     if(state != -1)
//         value = state;
//     return value;
// }

// void hanlder(int sig)
// {
//     (void)sig;
//     // Debug print to see if handler is called
//     write(2, "DEBUG: Signal handler called\n", 29);
	
//     if (signal_state(-1) == 0)
//     {
//         write(1, "\n", 1);
//         rl_on_new_line();
//         rl_replace_line("", 0);
//         rl_redisplay();
//     }
//     else if (signal_state(-1) == 1)
//     {
//         write(1, "\n", 1);
//         exit(130);
//     }
	
//     // Debug print to see which state we're in
//     char debug_msg[50];
//     int len = sprintf(debug_msg, "DEBUG: signal_state = %d\n", signal_state(-1));
//     write(2, debug_msg, len);
// }

// void signals()
// {
//     // Use sigaction instead of signal for more reliable behavior
//     struct sigaction sa;
//     sa.sa_handler = hanlder;
//     sigemptyset(&sa.sa_mask);
//     // sa.sa_flags = SA_RESTART; // This is important for readline
	
//     sigaction(SIGINT, &sa, NULL);
//     signal(SIGQUIT, SIG_IGN);
	
//     // Debug print
//     write(2, "DEBUG: Signal handlers installed\n", 33);
// }

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
