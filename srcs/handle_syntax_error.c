/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_syntax_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 11:54:49 by abdait-m          #+#    #+#             */
/*   Updated: 2021/04/22 14:09:42 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int     _char_in_tab_(char c, char tab[3])
{
    if (c == tab[0] || c == tab[1] || c == tab[2])
        return 1;
    return 0;
}

int     _is_white_space(char c)
{
    if (c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\r' || c == '\n')
        return 1;
    return 0;
}


int _check_semi_colon(char *line, t_mp *prs)
{
    prs->i++;
    if (line[0] == ';') // if the first chars is semicolon it is an t_mpor
    {
        prs->er = 1;
        return prs->i;
    }
    while (prs->i)
    {
        // if the char after the semicolon is one of this | or ; then it is an t_mpor
        if (line[prs->i] == '|' || line[prs->i] == ';')
        {
            prs->er = 1;
            break;
        }
        else if (_is_white_space(line[prs->i])) // skip while it's a white space
            prs->i++;
        else
            break; // break if nothing above was executed
    }
    return(--prs->i);// for knowing the char that we break at .... pardon my english hahaha
}

int _check_pipe(char *line, t_mp *prs)
{
    prs->i++;
                // if the first char is pipe or the next one is backslash zero then it is an t_mpor
    if (line[0] == '|' || !line[prs->i + 1])
    {
        prs->er = 1;
        return prs->i;
    }
    while (line[prs->i])
    {
        // Skip white spaces :
        if (_is_white_space(line[prs->i]))
            prs->i++;
        else if (line[prs->i] == '|' || line[prs->i] == ';' || line[prs->i] == '>' || line[prs->i] == '<') // Raise an exception if this condtion true
        {
            prs->er = 1;
            break;
        }
        else
            break;
    }
    return (--prs->i);
}

int _check_redirection(char *line, t_mp *prs)
{
    prs->credir = 1;
    prs->i++;
    // if (line[0] == '>' || line[0] == '<')
    // {
    //     prs->er = 1;
    //     return prs->i;
    // }
    while (line[prs->i])
    {
        // Start counting the redirection > 
        if (prs->tmp == '>' && line[prs->i] == '>')
        {
            prs->tmp = '>';
            prs->credir += 1;
            prs->i++;
        }
        else if (line[prs->i + 1] && prs->tmp == '>' && _is_white_space(line[prs->i]) && line[prs->i + 1] == '>') // This condition for this case for example  > > 
        {
            prs->er = 1;
            return prs->i;
        }
        else if (_is_white_space(line[prs->i]))
            prs->i++; // this condition for ; and | after redir | this  for > after < | this for  > or < after < | this for counting the number of redirection >  
        else if (line[prs->i] == ';' || line[prs->i] == '|' || (line[prs->i] == '<' && prs->tmp == '>') || (prs->tmp == '<' && (line[prs->i] == '>' || line[prs->i] == '<')) || prs->credir >= 3)
        {
            prs->er = 1;
            return prs->i;
        }
        else
            break;
    }
    if (!line[prs->i])
        prs->er = 1;
    return (--prs->i);
}

int _check_double_quotes(char *line, t_mp *prs)
{
    prs->i++;
    while (line[prs->i] != prs->tmp && line[prs->i])
    {
        // if you find backslash skip too chars the current one and the next one :
        if (line[prs->i] == '\\' && line[prs->i + 1] != '\0')
        {
            prs->i += 2;
            continue;
        }
        prs->i++;
    }
    if (line[prs->i] != prs->tmp) // this for checking the double quotes exists : else we raise an exception
        prs->er = 1; 
    return prs->i;
}

int _check_single_quotes(char *line, t_mp *prs)
{
    prs->i++;
    while (line[prs->i] != '\'' && line[prs->i])
        prs->i++;
    if (line[prs->i] != prs->tmp) // checking that the last chars after loop is single quotes else it is an t_mpor
        prs->er = 1;
    return prs->i;
}

int _handle_syntax_errors(char *line, t_mp *prs)
{

    prs->i = 0;
    // puts("im in");
    prs->er = 0;
    while (line[prs->i])
    {
        prs->tmp = line[prs->i];
        // Check t_mpors of semicolon :
        if (line[prs->i] == ';')
            prs->i = _check_semi_colon(line, prs);
        else if (line[prs->i] == '|') 
            prs->i = _check_pipe(line, prs);
        else if ((line[prs->i] == '>' || line[prs->i] == '<')) // Check errors of redirection :
            prs->i = _check_redirection(line, prs);
        else if (prs->tmp == '"') // Check errors of double quotes :
           prs->i = _check_double_quotes(line, prs);
        else if (prs->tmp == '\'') // Check errors of single quotes :
           prs->i = _check_single_quotes(line, prs);
        if (prs->er)
            return 1;
       prs->i++;
    }
    return (0);
}


void        _raise_an_exception()
{
    write(1, "mini$hell: Syntax error .\n", 26);
}