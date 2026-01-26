/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdadak <sdadak@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 22:40:14 by sdadak            #+#    #+#             */
/*   Updated: 2026/01/25 22:40:14 by sdadak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    ft_arr_free(char **arr)
{
    int i;

    i = 0;
    if (!arr)
        return ;
    while (arr[i])
        free(arr[i++]);
    free(arr);
}

void    ft_add_redir(t_cmd *cmd, t_redir *new_redir)
{
    t_redir *redir;

    if (!(cmd->redir))
        cmd->redir = new_redir;
    else
    {
        redir = cmd->redir;
        while (redir->next != NULL)
            redir = redir->next;
        redir->next = new_redir;        
    }
    new_redir->next = NULL;
}

void    ft_add_cmd(t_mdata *data, t_cmd *newcmd)
{
    t_cmd   *temp;

    if (!(data->cmd))
        data->cmd = newcmd;
    else
    {
        temp = data->cmd;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newcmd;
    }
    newcmd->next = NULL;
}

void    ft_cmd_free(t_cmd *cmd)
{
    t_cmd   *temp;
    t_redir *redir;
    t_redir *rtemp;

    if (!cmd)
        return ;
    while (cmd)
    {
        ft_arr_free(cmd->argv);
        redir = cmd->redir;
        while (redir)
        {
            free(redir->filename);
            rtemp = redir;
            redir = redir->next;
            free(rtemp);
        }
        temp = cmd;
        cmd = cmd->next;
        free(temp);
    }
}
