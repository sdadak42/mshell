/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdadak <sdadak@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:48:01 by sdadak            #+#    #+#             */
/*   Updated: 2026/01/21 16:48:01 by sdadak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char    *ft_joined(t_mdata *data, char *first, char *second)
{
    char    *newstr;

    newstr = ft_strjoin(first, second);
    free(first);
    free(second);
    if (!newstr)
        ft_error_malloc(data);
    return (newstr);
}

static int    ft_syntax_check_two(t_mdata *data, t_token *temp)
{
    if (ft_isoperator((int)(temp->value)[0]) && !temp->next)
    {
        ft_syntax_error(data, "newline");
        return (0);
    }
    else if (temp->type == PIPE && temp->next->type == PIPE)
    {
        ft_syntax_error(data, temp->next->value);
        return (0);
    }
    else if (temp->type == PIPE && ft_isoperator((int)(temp->next->value)[0]))
        return (1);
    else if (ft_isoperator((int)(temp->value)[0])
    && ft_isoperator((int)(temp->next->value)[0]))
    {
        ft_syntax_error(data, temp->next->value);
        return (0);
    }
    return (1);
}

int    ft_syntax_check(t_mdata *data)
{
    t_token *temp;

    temp = data->tokens;
    if (temp->type == PIPE)
    {
        ft_syntax_error(data, temp->value);
        return (0);
    }
    while (temp)
    {
        if (ft_syntax_check_two(data, temp) == 0)
            return (0);
        temp = temp->next;
    }
    return (1);
}