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

t_token	*ft_lexer_filter(char *line)
{
	t_token	*token;


}

void	ft_lexer(char *line)
{
	t_token	*token;
	int	i;
	int	j;

	token = malloc(sizeof(t_token));
	i = 0;
	j = 0;
	while (line[i])
	{
		if (ft_isalpha(line[i]))
		{
			j = i;
			while (ft_isalpha(line[i + 1]))
				i++;
			token->value = ft_substr(line, j, i - j + 1);
			token->type = WORD;
		}
		i++;
	}
	printf("value: %s\ntype: %d\n", token->value, token->type);
}

int	main(void)
{
	char	*line;

	while(1)
	{
		line = readline("minishell$> ");
		if (!line)
			return (rl_clear_history(), 0);
		if (*line)
		{
			add_history(line);
		}
		/* write(1, line, ft_strlen(line));
		write(1, "\n", 1); */
		ft_lexer(line);
		free(line);
	}
}
