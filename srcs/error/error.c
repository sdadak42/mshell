/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdadak <sdadak@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 18:05:07 by sdadak            #+#    #+#             */
/*   Updated: 2026/01/17 18:05:07 by sdadak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    ft_error_malloc(t_mdata *data)
{
    ft_mdata_free(data);
    perror("minishell");
    exit(1);
}

void    ft_mdata_free(t_mdata *data)
{
    if (!data)
        return ;
    ft_token_free(data);
    ft_env_free(data);
    if (data->line)
        free(data->line);
    data->line = NULL;
    free(data);
    data = NULL;
}

void    ft_syntax_error(t_mdata *data, char *token_value)
{
    write(2, "minishell: syntax error near unexpected token `", 47);
    write(2, token_value, ft_strlen(token_value));
    write(2, "'\n", 2);
    data->exit_status = SYNTAX_EXIT_CODE;
}