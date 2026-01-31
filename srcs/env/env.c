/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdadak <sdadak@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:09:33 by sdadak            #+#    #+#             */
/*   Updated: 2026/01/14 16:09:33 by sdadak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_add_env(t_mdata *data, char *key, char *value)
{
    t_env   *new_env;
	t_env	*temp;
    
    new_env = ft_calloc(1, sizeof(t_env));
    if (!new_env)
        ft_error_malloc(data);
    new_env->key = key;
    new_env->value = value;
	if (!(data->env))
		data->env = new_env;
	else
	{
		temp = data->env;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_env;
		new_env->next = NULL;
	}
}

static void    ft_env_copy(t_mdata *data, char **envp)
{
    int     i;
    int     j;
    char    *key;
    char    *value;

    i = 0;
    while (envp[i])
    {
        j = -1;
        while (envp[i][++j])
        {
            if (envp[i][j] == '=')
            {
                key = ft_substr(envp[i], 0, j);
                if (!key)
                    ft_error_malloc(data);
                value = ft_substr(envp[i], j + 1, ft_strlen(envp[i]) - j - 1);
                if (!value)
                    ft_error_malloc(data);
                ft_add_env(data, key, value);
                break ;
            }
        }
        i++;
    }
}

t_env   *ft_find_env(t_mdata *data, char *find_key)
{
    t_env   *temp;
    size_t  size;
    
    temp = data->env;
    while (temp)
    {
        if (ft_strlen(find_key) > ft_strlen(temp->key))
            size = ft_strlen(find_key);
        else
            size = ft_strlen(temp->key);
        if (ft_strncmp(temp->key, find_key, size) == 0)
            return (temp);
        temp = temp->next;
    }
    return (NULL);
}

char    **ft_env_to_arr(t_mdata *data)
{
    t_env   *lst;
    char    **arr;
    char    *temp;
    char    *result;
    int     i;

    i = 0;
    arr = ft_calloc(ft_env_size(data->env) + 1, sizeof(char *));
    if (!arr)
        ft_error_malloc(data);
    lst = data->env;
    while (lst)
    {
        temp = ft_strjoin(lst->key, "=");
        if (!temp)
            ft_error_malloc(data);
        result = ft_strjoin(temp, lst->value);
        if (!result)
            ft_error_malloc(data);
        free(temp);
        arr[i++] = result;
        lst = lst->next;
    }
    arr[i] = NULL;
    return (arr);
}

void    ft_env_init(t_mdata *data, char **envp)
{
    t_env   *shlvl;
    int     temp;
    char    *key;
    char    *value;

    ft_env_copy(data, envp);
    shlvl = ft_find_env(data, "SHLVL");
    if (!shlvl)
    {
        key = ft_strdup("SHLVL");
        if (!key)
            ft_error_malloc(data);
        value = ft_strdup("1");
        if (!value)
            ft_error_malloc(data);
        ft_add_env(data, key, value);
    }
    else
    {
        temp = ft_atoi(shlvl->value);
        free(shlvl->value);
        shlvl->value = ft_itoa(temp + 1);
        if (!shlvl->value)
            ft_error_malloc(data);
    }
}
