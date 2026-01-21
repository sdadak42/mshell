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
	if (temp /* && (temp->value)[0] != '\0' */)			//expand edilecek bişey yoksa ilk eleman \0 oluyor ve yazdırmıyor
	{
		while (temp)
		{
			write(1, temp->value, ft_strlen(temp->value));
			write(1, " ", 2);
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
			ft_mdata_free(data);
			exit(0);
		}
		data->line = line;
		if (ft_lexer(data, line) == 0)			// tırnak kapatılamışsa lexer 0 döner!
			add_history(line);
		else if (data->tokens)
		{
			add_history(line);
		// bundan sonrası parser'a taşınmalı
			if (ft_syntax_check(data))			// syntax hatası yoksa 1 döner
			{
				ft_expander(data);
				ft_joiner(data);
				token_yaz_gecici(data);
			}
		}
		ft_token_free(data);
		if (data->line)
		{
			free(data->line);
			data->line = NULL;
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_mdata		*data;

	(void)argc;
	(void)argv;
	data = ft_calloc(1, sizeof(t_mdata));
	if (!data)
		ft_error_malloc(data);
	ft_env_init(data, envp);
	ft_readline(data);
}