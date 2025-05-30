#include "minishell.h"

void handler_func(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
}

void signals(struct sigaction *sa)
{
	sigemptyset (&sa->sa_mask);
	sa->sa_handler = handler_func;
	sa->sa_flags = 0;
	sigaction(SIGINT, sa, NULL);
	signal(SIGQUIT, handler_func);
}