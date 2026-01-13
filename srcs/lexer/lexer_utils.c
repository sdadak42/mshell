/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdadak <sdadak@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 19:18:57 by sdadak            #+#    #+#             */
/*   Updated: 2026/01/13 19:18:57 by sdadak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_isoperator(int c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

int	ft_add_token(t_mdata *data, t_token *new_token)
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
	return ((int)ft_strlen(new_token->value));
}

void	ft_token_free(t_mdata *data)
{
	t_token	*token;
	t_token	*temp;

	token = data->tokens;
	while (token)
	{
		temp = token;
		token = token->next;
		free(temp->value);
		free(temp);
	}
	data->tokens = NULL;
}
