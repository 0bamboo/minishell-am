/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_vars_tools.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 14:01:12 by abdait-m          #+#    #+#             */
/*   Updated: 2021/04/26 23:30:35 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int     _is_special_(char c)
{
    // if ((c >= 32 && c <= 47 && c != 35 && c != 40 && c != 42 && c != 41 && c != 45 && c != 33) || (c >= 58 && c <= 63) || (c >= 91 && c <= 96) || ((c >= 123 && c <= 126)) || c == '\0')
    //     return 1;
    if (c == '_' || c == '@' || c == '&' || c == '!' || c == '#')
        return (1);
    return 0;
}


void _push_back_string_(char *buff, int index, char *fill, int size)
{
    while (*fill && size > 0)
    {
        buff[index++] = *fill++;
        size--;
    }
}

void _count_env_vars_(t_mp *prs)
{
    prs->count = 0;
    prs->j = ++prs->i;
    while ((ft_isalpha(prs->buffer[prs->j]) || ft_isdigit(prs->buffer[prs->i])) && prs->buffer[prs->j++])
        prs->count++;
    prs->temp = (char *)malloc(sizeof(char) * (prs->count + 1));
    prs->j = 0;
    while ((ft_isalpha(prs->buffer[prs->i]) || ft_isdigit(prs->buffer[prs->i])) && prs->buffer[prs->i])
        prs->temp[prs->j++] = prs->buffer[prs->i++];
    prs->temp[prs->j] = '\0';
    prs->env = getenv(prs->temp);
    if (prs->env)
        prs->counter += ft_strlen(prs->env);
    free(prs->temp);
    prs->temp = NULL;
}




void    _copy_dollar_digits_(t_mp *prs)
{
    if (prs->buffer[++prs->i] == 48)
    {
        _push_back_string_(prs->global, prs->g, "bash", 4);
        prs->g +=4;
        prs->i++;
    }
    else
        prs->i++;
}

void _copy_env_vars_(t_mp *prs)
{
    prs->count = 0;
    prs->j = ++prs->i;
    // counter++;
    // printf("first char = |%c|\n", prs->buffer[prs->i]);
    
    // This loop is for counting the length of the string that prs->i will look for its real value in envs vars....
    while ((ft_isalpha(prs->buffer[prs->j]) || ft_isdigit(prs->buffer[prs->i])) && prs->buffer[prs->j++])
        prs->count++;
    // Allocate the string 
    // if (prs->temp)
    //     free(prs->temp);
    prs->temp = (char *)malloc(sizeof(char) * (prs->count + 1));
    prs->j = 0;

    // Copy the string into prs->temp var....
    while ((ft_isalpha(prs->buffer[prs->i]) || ft_isdigit(prs->buffer[prs->i])) && prs->buffer[prs->i])
    {
        prs->temp[prs->j++] = prs->buffer[prs->i++];
    }
    prs->temp[prs->j] = '\0';
    // printf("prs->temp = |%s|\n", prs->temp);
    // prs->i--;

    // Look for the real value of that string using the function getenv...
    prs->env = getenv(prs->temp);
    // printf("prs->env = |%s|\n", prs->env);
    if (prs->env)
    {
        // If prs->i did found the env value for that string then prs->i will concatenate it with the prs->global string 
        prs->count = ft_strlen(prs->env);
        // counter += prs->count;
        _push_back_string_(prs->global, prs->g, prs->env, prs->count);
        prs->g += prs->count;
        // This one for moving the index of prs->global string...
    }
    free(prs->temp);
    prs->temp = NULL;
}