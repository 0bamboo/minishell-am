/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_vars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 11:48:20 by abdait-m          #+#    #+#             */
/*   Updated: 2021/04/28 15:20:07 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    _copy_command_status(t_mp *prs)
{
    char *tmp;
    
    tmp = ft_itoa(prs->status);
    prs->count = ft_strlen(tmp);
    _push_back_string_(prs->global, prs->g, tmp, prs->count);
    prs->g += prs->count;
    prs->i+=2;
    free(tmp);
}

void        _copy_inside_dq_(t_mp *prs)
{
    prs->global[prs->g++] = prs->buffer[prs->i++]; // copy the dq var
    while (prs->buffer[prs->i] != '"' && prs->buffer[prs->i])
    {
        // Loop throw the string inside dq..
        if (prs->buffer[prs->i] == '$' && ft_isdigit(prs->buffer[prs->i + 1]))
            _copy_dollar_digits_(prs);
        else if (prs->buffer[prs->i] == '\\')
        {
            // This case is one prs->i found the backslash so prs->i need to copy and skip two chars the current one and the next one,
            // This algorithm will help me for skipping the $var if the number of backslashes is odd and looking for $var if the number of bs is even...
            prs->global[prs->g++] = prs->buffer[prs->i++];
            prs->global[prs->g++] = prs->buffer[prs->i++];
        }
        else if (prs->buffer[prs->i] == '$' && _is_special_(prs->buffer[prs->i + 1]))
            prs->i += 2;
        else if (prs->buffer[prs->i] == '$' && ft_isalpha(prs->buffer[prs->i + 1]))
            _copy_env_vars_(prs);
        else if (prs->buffer[prs->i] == '$' && prs->buffer[prs->i + 1] == '?')
            _copy_command_status(prs);
        else // Copy the  other chars of inside dq "" ...
            prs->global[prs->g++] = prs->buffer[prs->i++];
    }
    prs->global[prs->g++] = prs->buffer[prs->i++];
}

void    _copy_inside_sq_(t_mp *prs)
{
    prs->global[prs->g++] = prs->buffer[prs->i++];
    while (prs->buffer[prs->i] && prs->buffer[prs->i] != '\'')
        prs->global[prs->g++] = prs->buffer[prs->i++];
    prs->global[prs->g++] = prs->buffer[prs->i++];
}


void _get_env_vars_2_(t_mp *prs)
{
    if (prs->buffer[prs->i] == '$' && prs->buffer[prs->i + 1] == '?')
        _copy_command_status(prs);
    else if (prs->buffer[prs->i] == '$' && _is_special_(prs->buffer[prs->i + 1]))
        prs->i += 2;
    else if (prs->buffer[prs->i] == '$' && ft_isdigit(prs->buffer[prs->i + 1]))
        _copy_dollar_digits_(prs);
    else if (prs->buffer[prs->i] == '$' && ft_isalpha(prs->buffer[prs->i + 1]))
        _copy_env_vars_(prs);
    else if (prs->buffer[prs->i] == '"')
        _copy_inside_dq_(prs);
    else if (prs->buffer[prs->i] == '\'')
        _copy_inside_sq_(prs);
    else
        prs->global[prs->g++] = prs->buffer[prs->i++];
}



char *_get_env_vars_(char *buffer, t_mp *prs)
{
    // char *global;
    int counter;

    prs->g = 0;
    counter = 0;
    prs->status = 12345;
    // This allocation is just for testing , but in the real project prs->i need to calculate,
    //how much memory prs->i will use first before changing the value of env variables.
    // printf("line counter = [%d]\n", _line_counter_(buffer));
    prs->buffer = buffer;
    counter = _line_counter_(prs);
    // printf("length = %d\n", counter);
    prs->global = (char *)malloc(sizeof(char *) * (counter + 1));
    prs->i = 0;
    while (prs->buffer[prs->i])
        _get_env_vars_2_(prs);
    prs->global[prs->g] = '\0';
    printf("after handling env : |%s|\n", prs->global);
    return prs->global;
}