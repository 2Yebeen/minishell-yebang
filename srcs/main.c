#include "../includes/minishell.h"

static void	shell_loop(t_minishell *sh);

t_global *g_val;

int	main(int ac, char *av[], char *envp[])
{
	t_minishell	*sh;

	(void)ac;
	(void)av;
	g_val = ft_calloc(1, sizeof(t_global));
	g_val->status = 0;
	g_val->env = envp;
	sh = ft_calloc(1, sizeof(sh));
	welcome_screen();
	set_signal();
	shell_loop(sh);
	return (0);
}

static void	shell_loop(t_minishell *sh)
{
	char	*read_line;

	while((read_line = readline("minishell $ ")))
	{
		if (*read_line != '\0' && !whitespace(read_line))
		{
			add_history(read_line);
			split_line(read_line, sh);
		}
		free(read_line);
	}
	printf("\033[1A");
	printf("\033[7C");
	printf("exit\n");
	exit(1);
}
