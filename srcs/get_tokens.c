/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeblee <yeblee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 13:39:55 by jibang            #+#    #+#             */
/*   Updated: 2022/08/26 01:43:12 by yeblee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	make_tokens_list(const char *str, t_list **token_list);
static void	make_alnum_token(char *line, int *i, t_list **token_list);
static void	make_d_quote_token(char *line, int *i, t_list **token_list);
static void	make_s_quote_token(char *line, int *i, t_list **token_list);
static void	make_parenthesis_token(char *line, int *i, t_list **token_list);
static void	lstadd_token_node(char *token, t_list **token_list);

t_list	*get_token_list(char *line)
{
	t_list	*token_list;

	token_list = NULL;
	make_tokens_list(line, &token_list);
	return (token_list);
}

static void	make_tokens_list(const char *str, t_list **token_list)
{
	char	*line;
	int		i;

	line = ft_strtrim(str, " ");
	i = 0;
	while (line[i])
	{
		make_alnum_token(line, &i, token_list);

		while (line[i] && !ft_isalnum(line[i]))
		{
			/* quotation case */
			if (line[i] == '\"')
				make_d_quote_token(line, &i, token_list);
			else if (line[i] == '\'')
				make_s_quote_token(line, &i, token_list);
			/* parenthesis case */
			else if (line[i] == '(')
				make_parenthesis_token(line, &i, token_list);
			/* | case */
			else if (line[i] == '|' && line[i + 1] != '|')
				lstadd_token_node(ft_substr(line, i, 1), token_list);
			else if (line[i] == '|' && line[i + 1] == '|')
			{
				lstadd_token_node(ft_substr(line, i, 2), token_list);
				i++;
			}
			/* & case */
			else if (line[i] == '&' && line[i + 1] != '&') // -> 예외처리!
				lstadd_token_node(ft_substr(line, i, 1), token_list);
			else if (line[i] == '&' && line[i + 1] == '&')
			{
				lstadd_token_node(ft_substr(line, i, 2), token_list);
				i++;
			}
			/* < case */
			else if (line[i] == '<' && line[i + 1] != '<')
				lstadd_token_node(ft_substr(line, i, 1), token_list);
			else if (line[i] == '<' && line[i + 1] == '<')
			{
				lstadd_token_node(ft_substr(line, i, 2), token_list);
				i++;
			}
			/* > case */
			else if (line[i] == '>' && line[i + 1] != '>')
				lstadd_token_node(ft_substr(line, i, 1), token_list);
			else if (line[i] == '>' && line[i + 1] == '>')
			{
				lstadd_token_node(ft_substr(line, i, 2), token_list);
				i++;
			}
			/* else */
			else
				lstadd_token_node(ft_substr(line, i, 1), token_list);
			i++;
		}
	}
}

static void	make_alnum_token(char *line, int *i, t_list **token_list)
{
	int		len;

	len = 0;
	while (line[*i] && ft_isalnum(line[*i]))
	{
		len++;
		(*i)++;
	}
	if (len > 0)
		lstadd_token_node(ft_substr(line, *i - len, len), token_list);
}

static void	make_d_quote_token(char *line, int *i, t_list **token_list)
{
	int		len;

	(*i)++;
	len = 0;
	while (line[*i] && line[*i] != '\"')
	{
		len++;
		(*i)++;
		if (line[*i - 1] == '\\' && line[*i] == '\"')
		{
			len++;
			(*i)++;
		}
	}
	if (line[*i] == '\"')
	{
		len++;
		(*i)++;
	}
	lstadd_token_node(ft_substr(line, *i - len - 1, len + 1), token_list);
	(*i)--;
}

static void	make_s_quote_token(char *line, int *i, t_list **token_list)
{
	int		len;

	(*i)++;
	len = 0;
	while (line[*i] && line[*i] != '\'')
	{
		len++;
		(*i)++;
	}
	if (line[*i] == '\'')
	{
		len++;
		(*i)++;
	}
	lstadd_token_node(ft_substr(line, *i - len - 1, len + 1), token_list);
	(*i)--;
}

static void	make_parenthesis_token(char *line, int *i, t_list **token_list)
{
	int		len;
	int		lcnt;
	int		rcnt;
	int		line_len;

	lcnt = 1;
	rcnt = 0;
	(*i)++;
	len = 0;
	line_len = ft_strlen(line);

	while (line[*i] && (lcnt != rcnt) && *i < line_len)
	{
		if (line[*i] == '(')
			lcnt++;
		if (line[*i] == ')')
		{
			rcnt++;
			while (line[*i] && (lcnt != rcnt) && *i < line_len)
			{
				len++;
				(*i)++;
				if (line[*i] == ')')
					rcnt++;
				if (line[*i] == '(')
					lcnt++;
			}
		}
		len++;
		(*i)++;
	}
	lstadd_token_node(ft_substr(line, *i - len - 1, len + 1), token_list);
	(*i)--;
}

static void	lstadd_token_node(char *token, t_list **token_list)
{
	t_list	*tmp;

	tmp = ft_lstnew(token);
	if (!tmp)
	{
		printf("Error\n");
		exit(1);
	}
	ft_lstadd_back(token_list, tmp);
}










