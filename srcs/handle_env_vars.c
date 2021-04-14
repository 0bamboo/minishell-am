/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_vars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 11:48:20 by abdait-m          #+#    #+#             */
/*   Updated: 2021/04/13 15:25:12 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int     _is_special_(char c)
{
    if ((c >= 32 && c <= 47) || (c >= 58 && c <= 64) || (c >= 91 && c <= 96) || ((c >= 123 && c <= 126)) || c == '\0')
        return 1;
    return 0;
}


void _add_to_string(char *buff, int index, char *fill, int size)
{
    // int i;

    // i = strlen(buff);
    // printf("index of start == |%d|,\n", index);
    // printf("size == |%d|, \n", size);
    // printf("first char of fill = |%c|\n", *fill);
    // printf("buff[%d]indx - 1 == |%c|\n", index-1, buff[index-1]);
    // printf("buff[%d]indx     == |%c|\n", index, buff[index]);
    while (*fill && size > 0)
    {
        // printf("|%c|\t,", *fill);
        buff[index++] = *fill++;
        size--;
    }
    // puts("");
}

void _count_dollar_digits_(ms_p *prs)
{
    if (prs->buffer[++prs->i] == 48)
    {
        prs->counter += 4;
        prs->i++;
    }
    else
        prs->i++;
}

void _count_env_vars_(ms_p *prs)
{
    int count;
    int j;
    char *fill;
    char *tmp;

    count = 0;
    j = ++prs->i;
    while (!(_is_special_(prs->buffer[j])) && prs->buffer[j++])
        count++;
    tmp = (char *)malloc(sizeof(char) * (count + 1));
    j = 0;
    while (!(_is_special_(prs->buffer[prs->i])) && prs->buffer[prs->i])
        tmp[j++] = prs->buffer[prs->i++];
    tmp[j] = '\0';
    fill = getenv(tmp);
    if (fill)
        prs->counter += ft_strlen(fill);
    if (tmp)
    {    
        free(tmp);
        tmp = NULL;
    }
    prs->i--;
}

void _dq_count_env_vars_(ms_p *prs)
{
    prs->count = 0;
    prs->j = ++prs->i;
    while (!(_is_special_(prs->buffer[prs->j])) && prs->buffer[prs->j++])
        prs->count++;
    prs->temp = (char *)malloc(sizeof(char) * (prs->count + 1));
    prs->j = 0;
    while (!(_is_special_(prs->buffer[prs->i])) && prs->buffer[prs->i])
        prs->temp[prs->j++] = prs->buffer[prs->i++];
    prs->temp[prs->j] = '\0';
    prs->fill = getenv(prs->temp);
    if (prs->fill)
        prs->counter += ft_strlen(prs->fill);
    if (prs->temp)
    {
        free(prs->temp);
        prs->temp = NULL;
    }
}

void _dq_count_dollar_digits_(ms_p *prs)
{
    if (prs->buffer[++prs->i] == 48)
    {
        prs->i++;
        prs->counter += 4;
    }
    else
        prs->i++;
}

void _count_inside_dq_(ms_p *prs)
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
        else if (prs->buffer[prs->i] == '$' && !(_is_special_(prs->buffer[prs->i + 1])))
            _dq_count_env_vars_(prs);
        else
        {
            prs->counter++;
            prs->i++;
        }
    }
}

void _count_inside_sq_(ms_p *prs)
{
    prs->i++;
    prs->counter++;
    while (prs->buffer[prs->i] && prs->buffer[prs->i] != '\'')
    {    
        prs->i++;
        prs->counter++;
    }
}


int _line_counter_(ms_p *prs)
{
    prs->i = -1;
    prs->counter = 0;
    // prs->buffer = buffer;
    while (prs->buffer[++prs->i])
    {
        if (prs->buffer[prs->i] == '$' && prs->buffer[prs->i + 1] == '?')
        {
            prs->i++;
            prs->counter++;
        }
        else if (prs->buffer[prs->i] == '$' && ft_isdigit(prs->buffer[prs->i + 1]))
        {
            _count_dollar_digits_(prs);
            prs->i--;
            continue;
        }
        else if (prs->buffer[prs->i] == '$' && !(_is_special_(prs->buffer[prs->i + 1])))
        {
            _count_env_vars_(prs);
            continue;
        }
        else if (prs->buffer[prs->i] == '"')
            _count_inside_dq_(prs);
        else if (prs->buffer[prs->i] == '\'')
            _count_inside_sq_(prs);
        if (prs->buffer[prs->i])
            prs->counter++;
    }
    return prs->counter;
}


void    _copy_dollar_digits_(ms_p *prs)
{
    if (prs->buffer[++prs->i] == 48)
    {
        _add_to_string(prs->global, prs->g, "bash", 4);
        prs->g +=4;
        prs->i++;
    }
    else
        prs->i++;
}

void _copy_env_vars_(ms_p *prs)
{
    prs->count = 0;
    prs->j = ++prs->i;
    // counter++;
    // printf("first char = |%c|\n", prs->buffer[prs->i]);
    
    // This loop is for counting the length of the string that prs->i will look for its real value in envs vars....
    while (!(_is_special_(prs->buffer[prs->j])) && prs->buffer[prs->j++])
        prs->count++;
    // Allocate the string 
    prs->temp = (char *)malloc(sizeof(char) * (prs->count + 1));
    prs->j = 0;

    // Copy the string into prs->temp var....
    while (!(_is_special_(prs->buffer[prs->i])) && prs->buffer[prs->i])
    {
        prs->temp[prs->j++] = prs->buffer[prs->i++];
    }
    prs->temp[prs->j] = '\0';
    // printf("prs->temp = |%s|\n", prs->temp);
    // prs->i--;

    // Look for the real value of that string using the function getenv...
    prs->fill = getenv(prs->temp);
    // printf("prs->fill = |%s|\n", prs->fill);
    if (prs->fill)
    {
        // If prs->i did found the env value for that string then prs->i will concatenate it with the prs->global string 
        prs->count = ft_strlen(prs->fill);
        // counter += prs->count;
        _add_to_string(prs->global, prs->g, prs->fill, prs->count);
        prs->g += prs->count;
        // This one for moving the index of prs->global string...
    }
    if (prs->temp)
    {    
        // Freeing the prs->temp string
        free(prs->temp);
        prs->temp = NULL;
    }
    prs->i--;
}

void _dq_copy_dollar_digits_(ms_p *prs)
{
    // The same case when prs->i found digits after dollar char...
    if (prs->buffer[++prs->i] == 48)
    {
        _add_to_string(prs->global, prs->g, "bash", 4);
        prs->g +=4;
        prs->i++;
    }
    else
        prs->i++;
}

void    _dq_copy_env_vars_(ms_p *prs)
{
    // Same thing when you found the $var...
    prs->count = 0;
    prs->j = ++prs->i;
    while (!(_is_special_(prs->buffer[prs->j])) && prs->buffer[prs->j++])
        prs->count++;
    prs->temp = (char *)malloc(sizeof(char) * (prs->count + 1));
    prs->j = 0;
    while (!(_is_special_(prs->buffer[prs->i])) && prs->buffer[prs->i])
        prs->temp[prs->j++] = prs->buffer[prs->i++];
    prs->temp[prs->j] = '\0';
    prs->fill = getenv(prs->temp);
    if (prs->fill)
    {
        prs->count = ft_strlen(prs->fill);
        _add_to_string(prs->global, prs->g, prs->fill, prs->count);
        prs->g += prs->count;
    }
    if (prs->temp)
    {
        free(prs->temp);
        prs->temp = NULL;
    }
}

void        _copy_inside_dq_(ms_p *prs)
{
    prs->global[prs->g++] = prs->buffer[prs->i++]; // copy the dq var
    while (prs->buffer[prs->i] != '"' && prs->buffer[prs->i])
    {
        // Loop throw the string inside dq..
        if (prs->buffer[prs->i] == '$' && ft_isdigit(prs->buffer[prs->i + 1]))
            _dq_copy_dollar_digits_(prs);
        else if (prs->buffer[prs->i] == '\\')
        {
            // This case is one prs->i found the backslash so prs->i need to copy and skip two chars the current one and the next one,
            // This algorithm will help me for skipping the $var if the number of backslashes is odd and looking for $var if the number of bs is even...
            prs->global[prs->g++] = prs->buffer[prs->i++];
            prs->global[prs->g++] = prs->buffer[prs->i++];
        }
        else if (prs->buffer[prs->i] == '$' && !(_is_special_(prs->buffer[prs->i + 1])))
            _dq_copy_env_vars_(prs);
        else // Copy the  other chars of inside dq "" ...
            prs->global[prs->g++] = prs->buffer[prs->i++];
    }
}

void    _copy_inside_sq_(ms_p *prs)
{
    prs->global[prs->g++] = prs->buffer[prs->i++];
    while (prs->buffer[prs->i] && prs->buffer[prs->i] != '\'')
        prs->global[prs->g++] = prs->buffer[prs->i++];
}

char *_get_env_vars_(char *buffer, ms_p *prs)
{
    // char *global;
    int counter;

    prs->g = 0;
    counter = 0;
    // This allocation is just for testing , but in the real project prs->i need to calculate,
    //how much memory prs->i will use first before changing the value of env variables.
    // printf("line counter = [%d]\n", _line_counter_(buffer));
    prs->buffer = buffer;
    counter = _line_counter_(prs);
    printf("length = %d\n", counter);
    prs->global = (char *)malloc(sizeof(char *) * (counter + 1));
    prs->i = -1;
    while (prs->buffer[++prs->i])
    {
        if (prs->buffer[prs->i] == '$' && prs->buffer[prs->i + 1] == '?')
            prs->global[prs->g++] = prs->buffer[prs->i++];
        else if (prs->buffer[prs->i] == '$' && ft_isdigit(prs->buffer[prs->i + 1]))
        {
            _copy_dollar_digits_(prs);
            prs->i--;
            continue;
        }
        else if (prs->buffer[prs->i] == '$' && !(_is_special_(prs->buffer[prs->i + 1])))
        {
            _copy_env_vars_(prs);
            continue;
        }
        else if (prs->buffer[prs->i] == '"')
            _copy_inside_dq_(prs);
        else if (prs->buffer[prs->i] == '\'')
            _copy_inside_sq_(prs);
        prs->global[prs->g++] = prs->buffer[prs->i];
    }
    prs->global[prs->g] = '\0';
    return prs->global;
}