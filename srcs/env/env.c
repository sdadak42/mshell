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
        j = 0;
        while (envp[i][j])
        {
            if (envp[i][j] == '=')
            {
                key = ft_substr(envp[i], 0, j);
                value = ft_substr(envp[i], j + 1, ft_strlen(envp[i]) - j - 1);
                ft_add_env(data, key, value);
                break ;
            }
            j++;
        }
        i++;
    }
}

t_env   *ft_find_env(t_mdata *data, char *find_key)
{
    t_env   *temp;
    
    temp = data->env;
    while (temp)
    {
        if (ft_strncmp(temp->key, find_key, ft_strlen(temp->key)) == 0)
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
    lst = data->env;
    while (lst)
    {
        temp = ft_strjoin(lst->key, "=");
        result = ft_strjoin(temp, lst->value);
        free(temp);
        arr[i] = result;
        lst = lst->next;
        i++;
    }
    arr[i] = NULL;
    return (arr);
}

void    ft_env_init(t_mdata *data, char **envp)
{
    t_env   *shlvl;

    ft_env_copy(data, envp);
    shlvl = ft_find_env(data, "SHLVL");
    if (!shlvl)
        ft_add_env(data, "SHLVL", ft_strdup("1"));
    else
        shlvl->value = ft_itoa(ft_atoi(shlvl->value) + 1);
}
