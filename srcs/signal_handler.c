#include "../includes/minishell.h"

static void	sig_handler(int	signo);

void	set_signal(void)
{
	signal(SIGINT, sig_handler); // ctrl + c
	signal(SIGQUIT, SIG_IGN); // ctrl +'\'
}

static void	sig_handler(int	signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	return ;
}