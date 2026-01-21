#ifndef MINISHELL_H
# define MINISHELL_H

# include "./Libft/libft.h"
//# include "./ft_printf/ft_printf.h" // GECICI - ft_printf
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define SYNTAX_EXIT_CODE 2


typedef enum e_token_type {
	WORD,
	HEREDOC,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	PIPE,
} t_type;

typedef struct s_token {
	char			*value;
	t_type			type;
	int				is_squote; 		// tek tırnak mı?
	int				is_join;   		// kendinden sonraki ile birleşik mi olacak?
	struct s_token	*next;
} t_token;

typedef struct s_env {
	char			*key;
	char			*value;
	struct s_env	*next;
} t_env;

typedef struct s_mdata {
	t_token		*tokens;
	t_env		*env;
	char		*line;
	int			exit_status;
} t_mdata;


//------------- LEXER FUNCTIONS ----------
int	ft_lexer(t_mdata *data, char *line);

//--- Utils
int		ft_isoperator(int c);
int		ft_add_token(t_mdata *data, t_token *new_token);
void	ft_token_free(t_mdata *data);


//-------------- ENV FUNCTIONS ------------
void    ft_env_init(t_mdata *data, char **envp);
void	ft_add_env(t_mdata *data, char *key, char *value);
t_env   *ft_find_env(t_mdata *data, char *find_key);
char    **ft_env_to_arr(t_mdata *data);

//---- Utils
int	ft_env_size(t_env *env);
void	ft_env_free(t_mdata *data);


//--------------- ERROR FUNCTIONS -----------
void    ft_error_malloc(t_mdata *data);
void    ft_mdata_free(t_mdata *data);
void    ft_syntax_error(t_mdata *data, char *token_value);


//--------------- PARSER FUNCTIONS -----------
int    ft_syntax_check(t_mdata *data);
void    ft_expander(t_mdata *data);
void    ft_joiner(t_mdata *data);


//----- Utils
char    *ft_joined(t_mdata *data, char *first, char *second);


#endif