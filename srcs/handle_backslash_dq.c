/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_backslash_dq.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 11:58:13 by abdait-m          #+#    #+#             */
/*   Updated: 2021/04/21 23:24:34 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char _ret_special(char buffer)
{
    if (buffer == '\\')
        return ('\\');
    else if (buffer == '"')
        return '"';
    else if (buffer == '$')
        return '$';
    else
        return 0;
}
int _is_special(char c)
{
    if (c == '\\' || c == '"' || c == '$' || c == '`')
        return 1;
    return 0;
}
void        _bs_for_double_quotes_(t_mp *prs, char *token)
{
    // prs->buffer[prs->j++] = token[prs->i++];
    prs->i++;
    while (token[prs->i] != '"')
    {
        if (token[prs->i] == '\\' && _is_special(token[prs->i + 1]))
        {
            prs->buffer[prs->j++] = _ret_special(token[prs->i + 1]);
            prs->i += 2;
            continue;
        }
        prs->buffer[prs->j++] = token[prs->i++];
    }
    prs->i++;
    // prs->buffer[prs->j++] = token[prs->i++];
}


void        _bs_for_single_quotes_(t_mp *prs, char *token)
{
    // prs->buffer[prs->j++] = token[prs->i++];
    prs->i++;
    while (token[prs->i] != '\'')
        prs->buffer[prs->j++] = token[prs->i++];
    prs->i++;
    // prs->buffer[prs->j++] = token[prs->i++];
}


char *_handle_backslash_(t_mp *prs, char *token)
{   
    int len;
    
    len = ft_strlen(token);
    prs->i = 0;
    prs->j = 0;
    prs->buffer = (char *)malloc(sizeof(char) * (len + 1));
    while (prs->i < len)
    {
        if (token[prs->i] == '"')
            _bs_for_double_quotes_(prs, token);
        else if (token[prs->i] == '\'')
            _bs_for_single_quotes_(prs, token);
        else
            prs->buffer[prs->j++] = token[prs->i++];
    }
    prs->buffer[prs->j] = '\0';
    free(token);
    return (prs->buffer);
}