#include "../includes/minishell.h"

t_token	*new_token(char *data, int type)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = type;
	new->data = data;
	return (new);
}

void	add_token(t_token *tokens, t_token *new)
{
	t_token	*buf;

	if (!new || !tokens)
		return ;
	if (!tokens)
	{
		tokens = new;
		return ;
	}
	buf = last_token(tokens);
	buf->next = new;
}

t_token	*last_token(t_token	*tokens)
{
	t_token	*buf;

	if (!tokens)
		return (NULL);
	buf = tokens;
	while(buf->next)
		buf = buf->next;
	return (buf);
}

void	del_token(t_token *tokens)
{
	t_token	*del;

	while (tokens)
	{
		del = tokens;
		tokens = tokens->next;
		free(del->data);
		free(del->next);
	}
	free(tokens);
}