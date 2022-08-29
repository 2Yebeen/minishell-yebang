#include "../includes/minishell.h"

static int	get_token_list(t_token *tokens, char *str);
static void	parse(t_node *node);

void	split_line(const char *str, t_minishell *sh)
{
	int		i;
	char	**line;

	i = -1;
	line = ft_split(str, ';');
	while (line[++i])
	{
		// 오류가 있을 경우
		if (!get_token_list(sh->tokens, line[i]))
			del_token(sh->tokens);
		else
		{
			sh->root = create_node(sh->tokens);
			parse(sh->root);
			del_node(sh->root);
			sh->root = NULL;
		}
		free(line[i]);
	}
	free(line);
}

static int	get_token_list(t_token *tokens, char *str)
{
	char	*line;

	line = ft_strtrim(str, " ");
	if (!check_syntax_error(tokens, line))
		return (FALSE);
	return (TRUE);
}

static void	parse(t_node *node)
{
	t_token	*root;

	if (node)
	{
		root = is_and_or_pipe(node->tokens);
		set_node_type(node, root);
		if (node->type == TK_AND || node->type == TK_OR || node->type == TK_PIPE)
		{
			insert_node(node->tokens, root);
			node->left = create_node(node->tokens);
			node->tokens = NULL;
			node->right = create_node(root->next);
			del_token(root);
			parse(node->left);
			parse(node->right);
		}
		else
		{
			
		}
	}
}