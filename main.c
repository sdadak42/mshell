/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdadak <sdadak@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 23:02:29 by sdadak            #+#    #+#             */
/*   Updated: 2026/01/08 23:42:26 by sdadak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_yaz_gecici(t_mdata *data)
{
	t_token *temp;

	temp = data->tokens;
	if ((temp->value)[0] != '\0')
	{
		while (temp)
		{
			write(1, temp->value, ft_strlen(temp->value));
			if (temp->is_join == 0)
				write(1, " ", 1);
			temp = temp->next;
		}
		write(1, "\n", 1);
	}
}
void	ft_readline(t_mdata *data)
{
	char		*line;

	while(1)
	{
		line = readline("minishell$> ");
		if (!line)			// ctrl-D basıldığında readline null döner
		{
			rl_clear_history();
			exit(0);
		}
		if (*line && ft_lexer(data, line))		// Hata yoksa(tokenlar oluşmuşsa) lexer 1 döner.
		{
			add_history(line);
			token_yaz_gecici(data);
			// lexerdan sonra çalışması gereken ne varsa buraya gelmeli!
		}
		ft_token_free(data);
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_mdata		*data;

	(void)argc;
	(void)argv;
	data = ft_calloc(1, sizeof(t_mdata));
	ft_env_init(data, envp);
	ft_readline(data);
}
