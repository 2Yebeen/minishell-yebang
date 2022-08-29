#include "../includes/minishell.h"

void	ft_perror(char *str)
{
	printf("%s %s\n", str, strerror(errno));
}

int	whitespace(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != 32 && !(line[i] >= 9 && line[i] <= 13))
			return (0);
		i++;
	}
	return (1);
}