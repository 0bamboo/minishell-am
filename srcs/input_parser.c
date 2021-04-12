/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 18:38:31 by abdait-m          #+#    #+#             */
/*   Updated: 2021/04/12 23:51:55 by abdait-m         ###   ########.fr       */
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


int _check_semi_colon(char *line, ms_p *prs)
{
    prs->i++;
    if (line[0] == ';') // if the first chars is semicolon it is an ms_por
    {
        prs->er = 1;
        return prs->i;
    }
    while (prs->i)
    {
        // if the char after the semicolon is one of this | or ; then it is an ms_por
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

int _check_pipe(char *line, ms_p *prs)
{
    prs->i++;
                // if the first char is pipe or the next one is backslash zero then it is an ms_por
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
        else if (line[prs->i] == '|' || line[prs->i] == ';') // Raise an exception if this condtion true
        {
            prs->er = 1;
            break;
        }
        else
            break;
    }
    return (--prs->i);
}

int _check_redirection(char *line, ms_p *prs)
{
    prs->credir = 1;
    prs->i++;
    while (line[prs->i])
    {
        // Start counting the redirection > 
        if (prs->tmp == '>' && line[prs->i] == '>')
        {
            puts("hi");
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

int _check_double_quotes(char *line, ms_p *prs)
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

int _check_single_quotes(char *line, ms_p *prs)
{
    prs->i++;
    while (line[prs->i] != '\'' && line[prs->i])
        prs->i++;
    if (line[prs->i] != prs->tmp) // checking that the last chars after loop is single quotes else it is an ms_por
        prs->er = 1;
    return prs->i;
}

int _handle_syntax_errors(char *line, ms_p *prs)
{

    prs->i = 0;
    // puts("im in");
    prs->er = 0;
    while (line[prs->i])
    {
        prs->tmp = line[prs->i];
        // Check ms_pors of semicolon :
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

void        _initialize_vars(s_split *ps)
{
    ps->check_dq = 0;
    ps->check_sq = 0;
    ps->i = 0;
    
}


void        _free_tokens_data_(t_cmd_list **head)
{
    int i;

    i = -1;
    if ((*head)->args)
    {
        while ((*head)->args[++i])
            free((*head)->args[i]);
        free((*head)->args);   
    }
    if ((*head)->command)
        free((*head)->command);
}


void        _free_all_tokens(t_cmd_list **head)
{
    t_cmd_list *next;
    
    if ((*head))
    {
        while (*head)
        {
            next = (*head)->next;
            _free_tokens_data_(head);
            free((*head));
            (*head) = next;
        }
        (*head) = NULL;
    }
}


void    _free_all_(ms_p *prs, t_cmd_list **head)
{
    // int i;

    // i = -1;
    _free_all_tokens(head);
    prs->err.i = 0;
    // if (prs->sc_cmds)
    // {
    //     while (prs->sc_cmds[++i])
    //             free(prs->sc_cmds[i]);
    //     free(prs->sc_cmds);
    //     prs->sc_cmds = NULL;
    // }
    
}

int     _check_for_special_chars_(char *buff)
{
    while (*buff)
    {
        if (_char_in_tab_(*buff, "><|"))
            return 1;
        buff++;
    }
    return 0;
}


void _push_back_normal_tokens_(char *line, t_cmd_list **head, ms_p *prs)
{
    t_cmd_list *curr;
    t_cmd_list *new;
    // s_split sp;
    
    //  use double pointer for declaring the struct ...
    prs->err.i = 0;
    // sp.i \\= 0;
    printf("line = '%s'\n", line);
    new = malloc(sizeof(t_cmd_list));
    new->prev = NULL;
    new->next = NULL;
    new->beg = 1;
    new->end = 1;
    // _initialize_vars(&sp);
    // new->args = _split_tokens(&sp, line, ' ');
    // new->command = ft_strdup(new->args[0]);
    if (!(*head))
    {
        (*head) = new;
    }
    else
    {
        curr = (*head);
        while (curr->next)
            curr =  curr->next;
        curr->next = new;
        new->prev = curr;
    }
}



void        _copy_tokens_data_(char *token, ms_p *prs, t_cmd_list **head)
{
    // prs->err.i = 0;
    // *head = NULL;
    // t_cmd_list *curr;
    if (token != NULL)
    {
        if (!_check_for_special_chars_(token))
        {
            _push_back_normal_tokens_(token, head, prs);
        }
        else
        {
            puts("special tokens");
        }
    }
    
    // else
        // Fill the data of special tokens find a way to _handle_syntax_errors this tokens that has pipes and redirs in it..
}

char _ret_special(char buffer)
{
    if (buffer == '\\')
        return ('\\');
    else if (buffer == '"')
        return '"';
    else if (buffer == '$')
        return '$';
    else if (buffer == '`') // this one is not needed
        return '`';
    else
        return 0;
}
int _is_special(char c)
{
    if (c == '\\' || c == '"' || c == '$' || c == '`')
        return 1;
    return 0;
}
void        _bs_for_double_quotes_(ms_p *prs, char *token)
{
    prs->buff[prs->j++] = token[prs->i++];
    while (token[prs->i] != '"')
    {
        if (token[prs->i] == '\\' && _is_special(token[prs->i + 1]))
        {
            puts("im in");
            prs->buff[prs->j++] = _ret_special(token[prs->i + 1]);
            prs->i += 2;
            continue;
        }
        prs->buff[prs->j++] = token[prs->i++];
    }
    prs->buff[prs->j++] = token[prs->i++];
}


void        _bs_for_single_quotes_(ms_p *prs, char *token)
{
    prs->buff[prs->j++] = token[prs->i++];
    while (token[prs->i] != '\'')
        prs->buff[prs->j++] = token[prs->i++];
    prs->buff[prs->j++] = token[prs->i++];
}


char *_handle_backslash_(ms_p *prs, char *token)
{   
    prs->i = 0;
    prs->j = 0;
    prs->buff = (char *)malloc(sizeof(char) * (ft_strlen(token) + 1));
    while (prs->i < (int)ft_strlen(token))
    {
        if (token[prs->i] == '"')
            _bs_for_double_quotes_(prs, token);
        else if (token[prs->i] == '\'')
            _bs_for_single_quotes_(prs, token);
        else
            prs->buff[prs->j++] = token[prs->i++];
    }
    prs->buff[prs->j] = '\0';
    return (prs->buff);
}

int     in(char *check, char c)
{
    while (*check)
    {
        if (*check == c)
            return 1;
        check++;
    }
    return 0;
}


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
            _count_dollar_digits_(prs);
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
            _copy_dollar_digits_(prs);
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

void _start_parsing(char *line, ms_p *prs, t_cmd_list **head)
{
    s_split sp;
    // int j;
    int i;
    // t_cmd_list *curr;
    
    // curr = *head;
    // curr->end = 0;
    puts("im in");
    _initialize_vars(&sp);
    if (_handle_syntax_errors(ft_strtrim(line, " \t\v\n"), prs))
        _raise_an_exception();
    else
    {
        puts("im in 2");
        prs->sc_cmds = _split_tokens(&sp, line, ';');
        printf("split|%s|\n", prs->sc_cmds[0]);
        // printf("|-%s-|\n", prs->sc_cmds[0]);
        i = -1;
        while (prs->sc_cmds[++i])
        {
            // i guess you need to handle the env variable before handling the backslash!!!!
            printf("before = |%s|\n", prs->sc_cmds[i]);
            prs->sc_cmds[i] = _get_env_vars_(prs->sc_cmds[i], prs);
            printf("after = |%s|\n", prs->sc_cmds[i]);
            if (in(prs->sc_cmds[i], '"'))
                prs->sc_cmds[i] = _handle_backslash_(prs, prs->sc_cmds[i]);
            printf("%d --> |%s| \n", i, prs->sc_cmds[i]);
            if (prs->sc_cmds[i] && prs->sc_cmds[i][0])
            {
                _copy_tokens_data_(prs->sc_cmds[i], prs, head);
            }
            // curr = (*head);
            // while (curr)
            // {
            //     printf("{%s}\n", curr->args[0]);
            //     curr = curr->next;
            // }
            // _free_all_(prs, head);
            // i = -1;
            // if (prs->sc_cmds)
            // {
            //     while (prs->sc_cmds[++i])
            //             free(prs->sc_cmds[i]);
            //     free(prs->sc_cmds);
            //     prs->sc_cmds = NULL;
            // }
            // while (curr)
            // {
            //     printf("dll = -> |%s| <-\n", curr->args[0]);   
            //     puts("1");
            //     curr = curr->next;
            // }
            // _free_all_(prs, head);
        }
    }
}