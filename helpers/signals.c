#include "../minishell.h"

void handler_parent(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
void handler_child(int sig)
{
	if (sig == SIGINT)
	{
		exit(1);
	}
}

void signals(struct sigaction *sa, int option)
{
	sigemptyset (&sa->sa_mask);
	if (option == 1)
		sa->sa_handler = handler_parent;
	else if (option == 2)
	{
		sa->sa_handler = handler_child;
	}
	sa->sa_flags = 0;
	sigaction(SIGINT, sa, NULL);
	signal(SIGQUIT, handler_parent);
}
