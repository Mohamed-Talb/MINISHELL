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
		exit(130);
	}
	if (signum == SIGQUIT)
	{
		write(1, "Quit (core dumped)\n", 20); // since we print /n in parent, this will cause a \nQuit....\n
		exit(131); 
	}
}

void heredoc_handler(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		exit(130);
	}
}

void do_nothing(int signum)
{
	(void)signum;
	write(1, "\n", 1);
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
	else if (mode == 3)
	{
		sa.sa_handler = heredoc_handler;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
	}
	else
	{
		sa.sa_handler = do_nothing;
		sigaction(SIGINT, &sa, NULL);     
		signal(SIGQUIT, SIG_IGN);
	}
}
