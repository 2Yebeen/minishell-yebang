#include "../includes/minishell.h"

static t_token	*pass_parens(t_token *tokens);

t_token	*is_and_or_pipe(t_token	*tokens)
{
	t_token	*buf;

	buf = tokens;
	while (buf)
	{
		if (buf->type == AND || buf->type == OR)
			return (buf);
		if (buf->type == PIPE)
			return (buf);
		if (buf->type == L_PARENS)
			buf = pass_parens(buf);
		buf = buf->next;
	}
	return (NULL);
}

static t_token	*pass_parens(t_token *tokens)
{
	int		cnt;
	t_token	*buf;

	cnt = 0;
	buf = tokens;
	while (buf)
	{
		if (buf->type == L_PARENS)
			cnt++;
		else if (buf->type == R_PARENS)
			cnt--;
		buf = buf->next;
		if (cnt == 0)
			break ;
	}
	return (buf);
}

void	set_node_type(t_node *node, t_token *token)
{
	if (!token)
	{
		if (node->type == APP_RD || node->type == INP_RD || token->type == OUT_RD || node->type == HERE_DOC)
			node->type = TK_REDIR;
		else if (node->type == L_PARENS || node->type == R_PARENS)
			node->type = TK_PARENS;
		else
			node->type = TK_WORD;
	}
	else if (token->type == AND)
		node->type = TK_AND;
	else if (token->type == OR)
		node->type = TK_OR;
	else if (token->type == PIPE)
		node->type = TK_PIPE;
}
