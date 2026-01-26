NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
LIBFT_DIR	= Libft
LIBFT		= $(LIBFT_DIR)/libft.a

SRCS		= main.c \
			  srcs/lexer/lexer.c \
			  srcs/lexer/lexer_utils.c \
			  srcs/env/env.c \
			  srcs/env/env_utils.c \
			  srcs/error/error.c \
			  srcs/parser/parser.c \
			  srcs/parser/parser_utils.c \
			  srcs/parser/expand.c \
			  srcs/parser/joiner.c \
			  srcs/parser/cmd.c \
			  srcs/parser/cmd_utils.c \
			  
OBJS		= $(SRCS:.c=.o)

all: $(LIBFT) $(PRINTF) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF) -lreadline -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -C $(LIBFT_DIR) clean
	@rm -f $(OBJS)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
