# ================ Color Variables ================ #
BLACK			= 	"\033[0;30m"
GRAY			= 	"\033[1;30m"
RED				=	"\033[0;31m"
GREEN			=	"\033[0;32m"
YELLOW			=	"\033[1;33m"
PURPLE			=	"\033[0;35m"
CYAN			=	"\033[0;36m"
WHITE			=	"\033[1;37m"
EOC				=	"\033[0;0m"
LINE_CLEAR		=	"\x1b[1A\x1b[M"
# ================================================= #

NAME			= minishell

CC				= cc
<<<<<<< HEAD
CFLAGS			= -Wall -Wextra -Werror -g -fsanitize=address
=======
CFLAGS			= -Wall -Wextra -Werror -g3 -fsanitize=address
>>>>>>> e497cc73b40e3479e8c60a6d027a27f372840489
RM				= rm -rf

LIB_READ		= -l readline
LDFLAGS			= -L$(shell brew --prefix readline)/lib
CPPFLAGS		= -I$(shell brew --prefix readline)/include

LIB_DIR			= lib/
LIBFT			= libft/libft.a
GNL				= get_next_line/libgnl.a
FTPRINT			= ft_printf/libftprintf.a

HEADERS			= includes

DIR_S 			= srcs
<<<<<<< HEAD
SOURCES			= 					\
				main.c				\
				check_syntax_error.c\
				parsing.c			\
				signal_handler.c	\
				utils_node.c		\
				utils_parsing.c		\
				utils_syntax_error.c\
				utils_token.c		\
				utils.c				\
				welcome_screen.c	
=======
SOURCES			= 				\
				minishell.c		
>>>>>>> e497cc73b40e3479e8c60a6d027a27f372840489

DIR_O			= objs
SRCS			= $(addprefix $(DIR_S)/,$(SOURCES))
OBJS			= $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

$(DIR_O)/%.o: $(DIR_S)/%.c $(HEADERS)/$(NAME).h
	@echo $(YELLOW) "Compiling...\t" $< $(EOC) $(LINE_CLEAR)
	@mkdir -p $(DIR_O)
	@$(CC) $(CFLAGS) -I $(HEADERS) -c $< -o $@

$(NAME): $(OBJS)
	@echo $(GREEN) "Source files are compiled!\n" $(EOC)
	@make -j -C $(LIB_DIR)/libft
	@make -j -C $(LIB_DIR)/ft_printf
	@make -j -C $(LIB_DIR)/get_next_line
	@$(CC) $(CFLAGS) -o $@ $^ $(LIB_DIR)/$(LIBFT) $(LIB_DIR)/$(GNL) $(LIB_READ) $(LDFLAGS) $(CPPFLAGS)
	@make -j fclean -C $(LIB_DIR)/libft
	@make -j fclean -C $(LIB_DIR)/ft_printf
	@make -j fclean -C $(LIB_DIR)/get_next_line
	@echo $(GREEN) "$(NAME) is created!\n" $(EOC)

all: $(NAME)

clean:
	@echo $(YELLOW) "Cleaning object files..." $(EOC)
	@$(RM) $(DIR_O)
	@echo $(RED) "Object files are cleaned!\n" $(EOC)

fclean:	clean
	@echo $(YELLOW) "Removing $(NAME)..." $(EOC)
	@$(RM) $(NAME)
	@echo $(RED) "$(NAME) is removed!\n\n" $(EOC)

re:
	@make fclean
	@make all

.PHONY: all clean fclean re
