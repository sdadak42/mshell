/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdadak <sdadak@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 22:00:01 by sdadak            #+#    #+#             */
/*   Updated: 2026/01/14 22:00:01 by sdadak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_env_size(t_env *env)
{
    t_env   *temp;
	int	    i;

	i = 0;
    temp = env;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

void	ft_env_free(t_mdata *data)
{
	t_env	*env;
	t_env	*temp;

	env = data->env;
	while (env)
	{
		temp = env;
		env = env->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
	env = NULL;
}