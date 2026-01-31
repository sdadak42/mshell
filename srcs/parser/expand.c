/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdadak <sdadak@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 23:56:41 by sdadak            #+#    #+#             */
/*   Updated: 2026/01/19 23:56:41 by sdadak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char *get_env_value(t_mdata *data, char *key)
{
    char    *value;
    t_env   *env;

    if (!key)
        ft_error_malloc(data);
    env = ft_find_env(data, key);
    free(key);
    if (env)
        value = ft_strdup(env->value);
    else
        value = ft_strdup("");
    if (!value)
        ft_error_malloc(data);
    return (value);
}

static void ft_exp_question(t_mdata *data, t_token *token, int i)
{
    char    *exp;
    char  *piece;
    char  *temp;

    exp = ft_itoa(data->exit_status);
    if (!exp)
        ft_error_malloc(data);
    piece = ft_substr(token->value, 0, i);
    if (!piece)
        ft_error_malloc(data);
    temp = ft_joined(data, piece, exp);
    piece = ft_strdup(&token->value[i + 1 + 1]);
    if (!piece)
        ft_error_malloc(data);
    free(token->value);
    token->value = ft_joined(data, temp, piece);
}

static void ft_exp_word(t_mdata *data, t_token *token, int i)
{
    int     j;
    char    *exp;
    char    *piece;
    char    *temp;

    j = 0;
    while (ft_isalnum(token->value[i + 1 + j])
        || token->value[i + 1 + j] == '_')
        j++;
    exp = get_env_value(data, ft_substr(&token->value[i + 1], 0, j));
    piece = ft_substr(token->value, 0, i);
    if (!piece)
        ft_error_malloc(data);
    temp = ft_joined(data, piece, exp);
    piece = ft_strdup(&token->value[i + j + 1]);
    if (!piece)
        ft_error_malloc(data);
    free(token->value);
    token->value = ft_joined(data, temp, piece);
}

static int ft_is_exp(char *c)
{
    if (c[0] == '$' && (c[1] == '_' || ft_isalpha(c[1]) || c[1] == '?'))
        return (1);
    return (0);
}

void    ft_expander(t_mdata *data)
{
    t_token *token;
    int     i;

    token = data->tokens;
    while (token)
    {
        i = 0;
        if (token->type == WORD && token->is_squote == 0)
        {
            while (token->value[i])
            {
                if (ft_is_exp(&token->value[i]))
                {
                    if (token->value[i + 1] == '?')
                        ft_exp_question(data, token, i);
                    else
                        ft_exp_word(data, token, i);
                }
                else
                    i++;
            }
        }
        token = token->next;
    }
}
