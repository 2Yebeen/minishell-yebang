#include "../includes/minishell.h"

t_node	*create_node(t_token *tokens)
{
	int		type;
	t_node	*root;

	root = ft_calloc(1, sizeof(t_node));
	if (!root)
		return (NULL);
	type = tokens->type;
	root->type = type;
	root->tokens = tokens;
	return (root);
}

void	insert_node(t_token *token, t_token *root)
{
	if (!token || root)
		return ;
	while (token->next)
	{
		if (token->next == root)
			break;
		token = token->next;
	}
	token->next = NULL;
}

void	del_node(t_node *node)
{
	if (node)
	{
		del_node(node->left);
		del_node(node->right);
		del_token(node->tokens);
		free(node);
		node = NULL;
	}
}
