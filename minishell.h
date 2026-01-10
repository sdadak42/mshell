#ifndef MINISHELL_H
# define MINISHELL_H 

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./Libft/libft.h"

typedef enum e_token_type
{
	WORD,
    HEREDOC,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	PIPE,
}t_token_type;

typedef struct s_token
{
	char	*value;
	t_token_type	type;
	struct s_token	*next;
}t_token;

typedef struct s_mdata
{
    t_token    *tokens;
}t_mdata;


#endif