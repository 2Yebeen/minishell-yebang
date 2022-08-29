#include "../includes/minishell.h"

static int	make_token(t_token *tokens, char *line);
static int	check_parens(t_token *tokens);

int	check_syntax_error(t_token *tokens, char *line)
{
	int	flag;

	flag = make_token(tokens, line);
	if (flag)
	{
		if (flag == S_QUOTE)
			ft_perror("syntax error near unexpected token `\'");
		else if (flag == D_QUOTE)
			ft_perror("syntax error: unexpected token `\"");
		return (FALSE);
	}
	if (!check_parens(tokens))
		return (FALSE);
	return (TRUE);
}

static int	make_token(t_token *tokens, char *line)
{
	int	i;
	int	quote_flag;

	i = -1;
	quote_flag = 0;
	while(line[++i])
	{
		/*!따옴표 처리 수정 필요!*/
		quote_flag = is_quote(line[i], quote_flag);	// 따옴표 확인
		if (!quote_flag)	// 따옴표가 아닌 경우: and, or, pipe, redir 확인
		{
			if (!check_token_type(tokens, line, i)) // and, or, pipe, redir 아닐경우, 
				add_token(tokens, new_token(ft_substr(line, i, 1), CMD));
		}
		else	// 따옴표인경우 - > string 처리하는 함수 추가 필요
			add_token(tokens, new_token(ft_substr(line, i, 1), STR));
		i++;
	}
	return (quote_flag);
}

static int	check_parens(t_token *tokens)
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
		if (cnt < 0)
			break ;
		buf = buf->next;
	}
	if (cnt)
	{
		if (cnt > 0)
			ft_perror("syntax error: unexpected token `(");
		else if (cnt < 0)
			ft_perror("syntax error: unexpected token `)");
		del_token(tokens);
		return (FALSE);
	}
	return(TRUE);
}
