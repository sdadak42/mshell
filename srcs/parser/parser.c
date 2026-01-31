/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdadak <sdadak@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 18:56:34 by sdadak            #+#    #+#             */
/*   Updated: 2026/01/16 18:56:34 by sdadak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_free_loop(t_mdata *data)
{
	ft_token_free(data);
	ft_cmd_free(data->cmd);
	data->cmd = NULL;
	if (data->line)
	{
		free(data->line);
		data->line = NULL;
	}
}

void	ft_readline(t_mdata *data)
{
	char	*line;

	line = readline("minishell$> ");
	if (!line)			// ctrl-D basıldığında readline null döner
	{
		ft_mdata_free(data);
		exit(0);
	}
	data->line = line;
	if (ft_lexer(data, line) == 0)			// tırnak kapatılamışsa lexer 0 döner!
		add_history(line);
	else if (data->tokens)
	{
		add_history(line);
		if (ft_syntax_check(data))			// syntax hatası yoksa 1 döner
		{
			ft_expander(data);
			ft_joiner(data);
			ft_cmd_struct(data);
			cmd_yaz_gecici(data);
			//token_yaz_gecici(data);
		}
	}
}
