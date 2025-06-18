#include "../minishell.h"

void handler_parent(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void handler_child(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		exit(130);
	}
	else if (signum == SIGQUIT)
	{
		write(1, "Quit (core dumped)\n", 20);
		exit(131); 
	}
}

void signals(int mode)
{
	struct sigaction sa;

	sigemptyset(&sa.sa_mask);

	if (mode == 1)
	{
		sa.sa_handler = handler_parent;
		sigaction(SIGINT, &sa, NULL);     
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == 2)
	{
		sa.sa_handler = handler_child;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
	}
}
