/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdadak <sdadak@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 22:34:06 by sdadak            #+#    #+#             */
/*   Updated: 2026/01/25 22:34:06 by sdadak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void    ft_join_argv_two(t_mdata *data, t_cmd *cmd, char *value)
{
    int     i;
    char    **temp;

    i = 0;
    while (cmd->argv[i])
        i++;
    temp = malloc(sizeof(char *) * (i + 1 + 1));
    if (!temp)
        ft_error_malloc(data);
    i = 0;
    while (cmd->argv[i])
    {
        temp[i] = ft_strdup(cmd->argv[i]);
        if (!(temp[i]))
            ft_error_malloc(data);
        i++;
    }
    temp[i] = ft_strdup(value);
    if (!(temp[i]))
        ft_error_malloc(data);
    temp[i + 1] = NULL;
    ft_arr_free(cmd->argv);
    cmd->argv = temp;
}

static void    ft_join_argv(t_mdata *data, t_cmd *cmd, char *value)
{
    if (!(cmd->argv))
    {
        cmd->argv = malloc(sizeof(char *) * 2);
        if (!(cmd->argv))
            ft_error_malloc(data);
        cmd->argv[0] = ft_strdup(value);
        if (!(cmd->argv[0]))
            ft_error_malloc(data);
        cmd->argv[1] = NULL;
    }
    else
        ft_join_argv_two(data, cmd, value);
}

static void    ft_create_redir(t_mdata *data, t_token *token, t_cmd *cmd)
{
    t_redir *redir;

    redir = malloc(sizeof(t_redir));
    if (!redir)
        ft_error_malloc(data);
    redir->type = token->type;
    redir->filename = ft_strdup(token->next->value);
    if (!(redir->filename))
        ft_error_malloc(data);
    ft_add_redir(cmd, redir);
}

static t_token *ft_fill_cmd(t_mdata *data, t_token *token, t_cmd *cmd)
{
    if (token->type == WORD)
    {
        ft_join_argv(data, cmd, token->value);
        token = token->next;
    }
    else
    {
        ft_create_redir(data, token, cmd);
        token = token->next->next;
    }
    return (token);
}

void    ft_cmd_struct(t_mdata *data)
{
    t_token *token;
    t_cmd   *cmd;

    token = data->tokens;
    cmd = ft_calloc(1, sizeof(t_cmd));
    if (!cmd)
        ft_error_malloc(data);
    ft_add_cmd(data, cmd);
    while (token)
    {
        if (token->type == PIPE)
        {
            cmd = ft_calloc(1, sizeof(t_cmd));
            if (!cmd)
                ft_error_malloc(data);
            cmd->argv = NULL;
            cmd->redir = NULL;
            ft_add_cmd(data, cmd);
            token = token->next;
        }
        else
            token = ft_fill_cmd(data, token, cmd);
    }
}
