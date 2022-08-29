#include "../includes/minishell.h"

int	check_token_type(t_token *tokens, char *line, int i)
{
	int	type;

	type = 0;
	if (line[i] == '<')
		type = INP_RD;
	else if (line[i] == '>')
		type = OUT_RD;
	else if (line[i] == '|')
		type = PIPE;
	else if (line[i] =='&')
		type = AND;
	else if (line[i] == '(')
		type = L_PARENS;
	else if (line[i] == ')')
		type = R_PARENS;
	if (!check_type_double(tokens, line, i, type) && type)
	{
		if (type == AND)
			ft_perror("syntax error near unexpected token `&");
		else
			add_token(tokens, new_token(ft_substr(line, i, 1), type));
	}
	return (type);
}

int	check_type_double(t_token *tokens, char *line, int i, int type)
{
	if (line[i + 1])
	{
		if (line[i + 1] == '<' && type == INP_RD)
			type = HERE_DOC;
		else if (line[i + 1] == '>' && type == OUT_RD)
			type = APP_RD;
		else if (line[i + 1] == '|' && type == PIPE)
			type = OR;
		else if (line[i + 1] =='&' && type == AND)
			type = AND;
		else
			return (FALSE);
	}
	add_token(tokens, new_token(ft_substr(line, i, 2), type));
	return (TRUE);
}

int	is_quote(char c, int flag)
{
	if (!(flag == D_QUOTE) && c == '\'')
	{
		if (flag == S_QUOTE)
			flag = 0;
		else
			flag = S_QUOTE;
	}
	else if (!(flag == S_QUOTE) && c == '"')
	{
		if (flag == D_QUOTE)
			flag = 0;
		else
			flag = D_QUOTE;
	}
	return (flag);
}
