#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <signal.h>
# include <termios.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "../lib/libft/libft.h"
# include "../lib/ft_printf/ft_printf.h"
# include "../lib/get_next_line/get_next_line.h"

# define TRUE	1
# define FALSE	0

enum	e_token
{
	NONE,
	OR,
	AND,
	PIPE,
	CMD,
	S_QUOTE,
	D_QUOTE,
	STR,
	INP_RD,
	OUT_RD,
	APP_RD,
	HERE_DOC,
	L_PARENS,
	R_PARENS
};

enum	e_type
{
	TK_OR,
	TK_AND,
	TK_PIPE,
	TK_WORD,
	TK_REDIR,
	TK_PARENS
};

// token : 가장 작은 단위로 나눔
typedef struct s_token
{
	enum e_token	type;
	char			*data;
	struct s_token	*next;
}				t_token;

typedef struct s_node
{
	enum e_type		type;
	t_token			*tokens;
	struct s_node	*left;
	struct s_node	*right;
}				t_node;

typedef struct s_minishell
{
	t_node		*root;
	t_token		*tokens;
}				t_minishell;

typedef struct s_global
{
	int		status;
	char	**env;
}				t_global;

void	rl_replace_line (const char *text, int clear_undo);

/*	welcome_screen.c	*/
void	welcome_screen(void);

/*	utils_parsing.c	*/
t_token	*is_and_or_pipe(t_token	*tokens);
void	set_node_type(t_node *node, t_token *token);
/*	parsing.c	*/
void	split_line(const char *str, t_minishell *sh);

/*	signal_handler.c	*/
void	set_signal(void);

/*	check_syntax_error	*/
int		check_syntax_error(t_token *tokens, char *line);

/*	utils_syntax_error.c	*/
int		check_token_type(t_token *tokens, char *line, int i);
int		check_type_double(t_token *tokens, char *line, int i, int type);
int		is_quote(char c, int flag);

/*	utils_token.c	*/
t_token	*new_token(char *data, int type);
void	add_token(t_token *tokens, t_token *new);
t_token	*last_token(t_token	*tokens);
void	del_token(t_token *tokens);

/*	utils_node.c	*/
t_node	*create_node(t_token *tokens);
void	insert_node(t_token *token, t_token *root);
void	del_node(t_node *node);

/*	utils.c	*/
void	ft_perror(char *str);
int		whitespace(char *line);

#endif