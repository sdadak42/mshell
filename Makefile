NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
LIBFT_DIR	= Libft
LIBFT		= $(LIBFT_DIR)/libft.a
# GECICI - ft_printf
PRINTF_DIR	= ft_printf
PRINTF		= $(PRINTF_DIR)/libftprintf.a
# GECICI - ft_printf
SRCS		= main.c \
			  srcs/lexer/lexer.c \
			  srcs/lexer/lexer_utils.c
OBJS		= $(SRCS:.c=.o)

all: $(LIBFT) $(PRINTF) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

# GECICI - ft_printf
$(PRINTF):
	@make -C $(PRINTF_DIR)
# GECICI - ft_printf

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
