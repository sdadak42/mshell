/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joiner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdadak <sdadak@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 20:16:08 by sdadak            #+#    #+#             */
/*   Updated: 2026/01/21 20:16:08 by sdadak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    ft_joiner(t_mdata *data)
{
    t_token *tkn;
    t_token *temp;
    t_token *prev;

    prev = NULL;
    tkn = data->tokens;
    while (tkn)
    {
        if (tkn->type == WORD && tkn->is_join == 1)
        {
            tkn->next->value = ft_joined(data, tkn->value, tkn->next->value);
            if (!prev)
                data->tokens = tkn->next;
            else
                prev->next = tkn->next;
            temp = tkn;
            tkn = tkn->next;
            free(temp);
        }
        else
        {
            prev = tkn;
            tkn = tkn->next;
        }
    }
}
