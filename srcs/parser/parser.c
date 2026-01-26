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
