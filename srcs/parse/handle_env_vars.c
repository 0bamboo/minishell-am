/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_vars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 11:48:20 by abdait-m          #+#    #+#             */
/*   Updated: 2021/04/23 15:17:56 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int     _is_special_(char c)
{
    // if ((c >= 32 && c <= 47 && c != 35 && c != 40 && c != 42 && c != 41 && c != 45 && c != 33) || (c >= 58 && c <= 63) || (c >= 91 && c <= 96) || ((c >= 123 && c <= 126)) || c == '\0')
    //     return 1;
    if (c == '_' || c == '@' || c == '&' || c == '!')
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

void _count_dollar_digits_(t_mp *prs)
{
    if (prs->buffer[++prs->i] == 48)
    {
        prs->counter += 4;
        prs->i++;
    }
    else
        prs->i++;
}

void _count_env_vars_(t_mp *prs)
{
    prs->count = 0;
    prs->j = ++prs->i;
    while (ft_isalpha(prs->buffer[prs->j]) && prs->buffer[prs->j++])
        prs->count++;
    prs->temp = (char *)malloc(sizeof(char) * (prs->count + 1));
    prs->j = 0;
    while (ft_isalpha(prs->buffer[prs->i]) && prs->buffer[prs->i])
        prs->temp[prs->j++] = prs->buffer[prs->i++];
    prs->temp[prs->j] = '\0';
    prs->env = getenv(prs->temp);
    if (prs->env)
        prs->counter += ft_strlen(prs->env);
    free(prs->temp);
    prs->temp = NULL;
}

void _dq_count_dollar_digits_(t_mp *prs)
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
            _dq_count_dollar_digits_(prs);
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
    // printf("counter = |%d|\n", prs->counter);
    return prs->counter;
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
    while (ft_isalpha(prs->buffer[prs->j]) && prs->buffer[prs->j++])
        prs->count++;
    // Allocate the string 
    // if (prs->temp)
    //     free(prs->temp);
    prs->temp = (char *)malloc(sizeof(char) * (prs->count + 1));
    prs->j = 0;

    // Copy the string into prs->temp var....
    while (ft_isalpha(prs->buffer[prs->i]) && prs->buffer[prs->i])
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

void _dq_copy_dollar_digits_(t_mp *prs)
{
    // The same case when prs->i found digits after dollar char...
    if (prs->buffer[++prs->i] == 48)
    {
        _push_back_string_(prs->global, prs->g, "bash", 4);
        prs->g +=4;
        prs->i++;
    }
    else
        prs->i++;
}

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
    // printf("after handling env : |%s|\n", prs->global);
    free(buffer);
    return prs->global;
}