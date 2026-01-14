/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdadak <sdadak@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 19:14:19 by sdadak            #+#    #+#             */
/*   Updated: 2026/01/13 19:14:19 by sdadak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_token_word(t_mdata *data, char *line, int index)
{
	t_token	*token;
	int	i;

	i = index;
	token = ft_calloc(1 ,sizeof(t_token));
	while (!ft_isoperator(line[i]) && line[i] != ' ' && line[i] != '\''
	&& line[i] != '\"' && ft_isprint(line[i]))
		i++;
	if (line[i] != ' ' && !ft_isoperator(line[i]) && line[i] != '\0')
		token->is_join = 1;
	token->value = ft_substr(line, index, i - index);
	token->type = WORD;
	ft_add_token(data, token);
	return (i - index);
}

static int	ft_token_quote(t_mdata *data, char *line, int index)
{
	t_token	*token;
	int	i;
	int	temp_quo;

	i = index + 1;
	token = ft_calloc(1 ,sizeof(t_token));
	if (line[index] == '\'')
	{
		token->is_squote = 1;
		temp_quo = '\'';
	}
	else
		temp_quo = '\"';
	while (line[i] && line[i] != temp_quo)
		i++;
	if (line[i] == '\0')
		return (0);		// Kapanmamış tırnak hatası!
	if (line[i + 1] != ' ' && !ft_isoperator(line[i + 1])
	&& line[i + 1] != '\0')
		token->is_join = 1;
	token->value = ft_substr(line, index + 1, i - index - 1);
	token->type = WORD;
	ft_add_token(data, token);
	return (i - index + 1);
}

static int	ft_token_operator(t_mdata *data, char *line, int index)
{
	t_token	*token;

	token = ft_calloc(1 ,sizeof(t_token));
    if (line[index] == '|')
		token->type = PIPE;
	else if (line[index] == '<' && line[index + 1] == '<')
		token->type = HEREDOC;
	else if (line[index] == '>' && line[index + 1] == '>')
		token->type = APPEND;
	else if (line[index] == '<')
		token->type = REDIR_IN;
	else if (line[index] == '>')
		token->type = REDIR_OUT;
	if (token->type == PIPE)
		token->value = ft_strdup("|");
	else if (token->type == HEREDOC)
		token->value = ft_strdup("<<");
	else if (token->type == APPEND)
		token->value = ft_strdup(">>");
	else if (token->type == REDIR_IN)
		token->value = ft_strdup("<");
	else if (token->type == REDIR_OUT)
		token->value = ft_strdup(">");
    return (ft_add_token(data, token));
}

int	ft_lexer(t_mdata *data, char *line)
{
	int	i;
	int	temp;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			temp = ft_token_quote(data, line, i);
			if (temp == 0)
			{
				ft_putendl_fd("minishell: syntax error: unclosed quote",
					STDERR);
				return (data->exit_status = 2, 0);
			}
			i += temp;
		}
		else if (ft_isoperator(line[i]))
			i += ft_token_operator(data, line, i);
		else if (line[i] != ' ' && ft_isprint(line[i]))
			i += ft_token_word(data, line, i);
		else
			i++;
	}
	return (1);
}
