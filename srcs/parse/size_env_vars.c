/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_env_vars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 14:01:04 by abdait-m          #+#    #+#             */
/*   Updated: 2021/04/26 23:20:27 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void _count_dollar_digits_(t_mp *prs)
{
    if (prs->buffer[++prs->i] == 48)
    {
        prs->i++;
        prs->counter += 4;
    }
    else
        prs->i++;
}

void        _count_command_status(t_mp *prs)
{
    char *tmp;
    
    prs->i += 2;
    tmp = ft_itoa(prs->status);
    prs->counter += ft_strlen(tmp);
    free(tmp);
}

void _count_inside_dq_(t_mp *prs)
{
    prs->counter++;
    prs->i++;
    while (prs->buffer[prs->i] != '"' && prs->buffer[prs->i])
    {
        if (prs->buffer[prs->i] == '$' && ft_isdigit(prs->buffer[prs->i + 1]))
            _count_dollar_digits_(prs);
        else if (prs->buffer[prs->i] == '\\')
        {
            prs->i += 2;
            prs->counter += 2;
        }
        else if (prs->buffer[prs->i] == '$' && ft_isalpha(prs->buffer[prs->i + 1]))
            _count_env_vars_(prs);
        else if (prs->buffer[prs->i] == '$' && prs->buffer[prs->i + 1] == '?')
            _count_command_status(prs);
        else
        {
            prs->counter++;
            prs->i++;
        }
    }
    prs->counter++;
    prs->i++;
}

void _count_inside_sq_(t_mp *prs)
{
    prs->i++;
    prs->counter++;
    while (prs->buffer[prs->i] && prs->buffer[prs->i] != '\'')
    {    
        prs->i++;
        prs->counter++;
    }
    prs->i++;
    prs->counter++;
}


int _line_counter_(t_mp *prs)
{
    prs->i = 0;
    prs->counter = 0;
    while (prs->buffer[prs->i])
    {
        if (prs->buffer[prs->i] == '$' && prs->buffer[prs->i + 1] == '?')
            _count_command_status(prs);
        else if (prs->buffer[prs->i] == '$' && _is_special_(prs->buffer[prs->i + 1]))
            prs->i += 2;
        else if (prs->buffer[prs->i] == '$' && ft_isdigit(prs->buffer[prs->i + 1]))
            _count_dollar_digits_(prs);
        else if (prs->buffer[prs->i] == '$' && ft_isalpha(prs->buffer[prs->i + 1]))
            _count_env_vars_(prs);
        else if (prs->buffer[prs->i] == '"')
            _count_inside_dq_(prs);
        else if (prs->buffer[prs->i] == '\'')
            _count_inside_sq_(prs);
        else if (prs->buffer[prs->i])
        {
            prs->counter++;
            prs->i++;
        }
    }
    printf("counter = |%d|\n", prs->counter);
    return prs->counter;
}