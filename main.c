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

void	ft_add_token(t_mdata *data, t_token *new_token)
{
	t_token	*temp;

	if (!(data->tokens))
		data->tokens = new_token;
	else
	{
		temp = data->tokens;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_token;
		new_token->next = NULL;
	}
}

int	ft_token_word(t_mdata *data, char *line)
{
	t_token	*token;
	int	i;

	i = 0;
	token = malloc(sizeof(t_token));
	if (ft_isalpha(line[i]))
	{
		while (ft_isalpha(line[i]))
			i++;
		token->value = ft_substr(line, 0, i);
		token->type = WORD;
		token->next = NULL;
		ft_add_token(data, token);
	}
	return (i);
}

void	ft_lexer(t_mdata *data, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_isalpha(line[i]))
			i += ft_token_word(data, &line[i]);
		i++;
	}
}

int	main(void)
{
	t_mdata	*data;
	t_token	*temp;
	t_token	*freele;
	char	*line;

	data = malloc(sizeof(t_mdata));
	while(1)
	{
		line = readline("minishell$> ");
		if (!line)
			return (rl_clear_history(), 0);
		if (*line)
		{
			add_history(line);
		}
		ft_lexer(data, line);
		temp = data->tokens;
		while (temp)
		{
			write(1, temp->value, ft_strlen(temp->value));
			write(1, "\n", 1);
			temp = temp->next;
		}
		temp = data->tokens;
		while (temp)
		{
			freele = temp;
			temp = temp->next;
			free(freele->value);
			free(freele);
		}
		free(line);
	}
}
