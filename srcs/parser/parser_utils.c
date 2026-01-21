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
