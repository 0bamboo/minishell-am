/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 18:38:31 by abdait-m          #+#    #+#             */
/*   Updated: 2021/04/04 22:54:13 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int     _check_special_chars_(char check, char check_nx, ms_p *prs)
// {
//     if ((check == '|' || check == '>' || check == '\\' || check == '<') && check_nx == '\0')
//         return (1);
//     if (check == ';' && check_nx == '\0' && prs->err.len <= 2)
//         return 1;
//     if (check == ';' && prs->err.tmp == ';' && prs->err.dq == 0 && prs->err.sq == 0)
//         return 1;
//     return 0;
// }

int     _char_in_tab_(char c, char tab[3])
{
    if (c == tab[0] || c == tab[1] || c == tab[2])
        return 1;
    return 0;
}
// // fix spc space spc????????????????????????

// int  _check_4_repeated_spc_(char *buff)
// {
//     int nbrspc;
    
//     nbrspc = 0;
//     while (*buff)
//     {
//         if (_char_in_tab_(*buff, "|<>"))
//             nbrspc++;
//         else
//             nbrspc = 0;
//         if (nbrspc == 3)
//             return 1;
//         buff++;
//     }
//     return 0;
// }

// int     _check_near_spc_(char *buff)
// {
//     int     spc;
//     char    tmp;
    
//     spc = 0;
//     tmp = ' ';
//     while (*buff)
//     {
//         if ((*buff == '>' || *buff == '<' || *buff == '|') && tmp == ' ')
//             spc++;
//         else if (*buff == ' ' || *buff == '\t')
//         {
//             tmp = *buff;
//             buff++;
//             continue;
//         }
//         else
//             spc = 0;
//         buff++;
//         if (spc == 2)
//             return 1;
//         tmp = *buff;
//     }
//     return 0;
// }

// int     _check_backslash_error_(char *checker, int i)
// {
//     int counter;

//     counter = 0;
//     printf("cc--%c--cc--%d\n", checker[i], i);
//     while (checker[i] == '\\')
//     {
//         counter++;
//         i--;
//     }
//     if (counter % 2 == 0)
//         return 0;
//     return 1;
// }

// int _check_parsing_errors(char *line, ms_p *prs)
// {
//     int ret;

//     ret = 0;

//     prs->err.i = -1;
//     prs->err.sq = 0;
//     prs->err.dq = 0;
//     prs->err.countsq = 0;
//     prs->err.countdq = 0;
//     prs->err.tmp = '\0';
//     line = ft_strtrim(line, " \t\n\v");
//     prs->err.len = ft_strlen(line);
//     while (line[++prs->err.i])
//     {
//         if (line[0] == ';' || line[0] == '|' || ret)
//             return 1;
//         if (_check_special_chars_(line[prs->err.i], line[prs->err.i + 1], prs))
//             return 1;
//         if (line[prs->err.i] == '"' && prs->err.dq == 0 && prs->err.sq == 0)
//         {
//             prs->err.countdq++;
//             prs->err.dq = 1;
//         }
//         else if (line[prs->err.i] == '"' && prs->err.dq == 1)
//         {
//             prs->err.countdq--;
//             prs->err.dq = 0;
//             // if (_check_backslash_error_(line, prs->err.i - 1))
//             //     return 1;
//         }
//         if (line[prs->err.i] == '\'' && prs->err.sq == 0 && prs->err.dq == 0)
//         {
//             prs->err.countsq++;
//             prs->err.sq = 1;
//         }
//         else if (line[prs->err.i] == '\'' && prs->err.sq == 1)
//         {
//             prs->err.countsq--;
//             prs->err.sq = 0;
//         }
//         if (_char_in_tab_(line[prs->err.i], "<>|") && !prs->err.dq && !prs->err.sq)
//             ret = _check_4_repeated_spc_(line + prs->err.i) + _check_near_spc_(line + prs->err.i);
//         // if (prs->err.tmp == '\\' && line[prs->err.i] == '"' && prs->err.sq == 0 && prs->err.dq ==  0)
//         //     return (1);
//         prs->err.tmp = line[prs->err.i];
//     }
//     return (prs->err.countsq + prs->err.countdq);
// }

int _check_semi_colon(char *line, ms_p *prs)
{
    prs->i++;
    if (line[0] == ';') // if the first chars is semicolon it is an ms_por
    {
        prs->er = 1;
        return prs->i;
    }
    while (line[prs->i])
    {
        // if the char after the semicolon is one of this | or ; then it is an ms_por
        if (line[prs->i] == '|' || line[prs->i] == ';')
        {
            prs->er = 1;
            break;
        }
        else if (line[prs->i] == ' ') // skip while it's a white space
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
        if (line[prs->i] == ' ')
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
        else if (line[prs->i + 1] && prs->tmp == '>' && line[prs->i] == ' ' && line[prs->i + 1] == '>') // This condition for this case for example  > > 
        {
            prs->er = 1;
            return prs->i;
        }
        else if (line[prs->i] == ' ')
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
    printf("|%c|\n", line[prs->i]);
    if (line[prs->i] != prs->tmp) // checking that the last chars after loop is single quotes else it is an ms_por
        prs->er = 1;
    return prs->i;
}

int parse(char *line, ms_p *prs)
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



// int         _check_for_pipe(ms_p *prs, int current)
// {
//     int     i;
//     int     q;
//     int     dq;

//     i = 0;
//     q = 0;
//     dq = 0;
//     while (prs->sc_cmds[current][i])
//     {
//         if (prs->sc_cmds[current][i] == '"' && dq == 0 && q == 0)
//             dq = 1;
//         else if (prs->sc_cmds[current][i] == '\'' && q == 0 && dq == 0)
//             q = 1;
//         else if (prs->sc_cmds[current][i] == '|' && dq == 0 && q == 0)
//             return i;
//         else if (prs->sc_cmds[current][i] == '"' && dq == 1)
//             dq = 0;
//         else if (prs->sc_cmds[current][i] == '\'' && q == 1)
//             q = 0;
//         i++;
//     }
//     return (0);
// }

void        _push_back_tokens(t_cmd_list **head, char **cmds)
{
    t_cmd_list *curr;
    t_cmd_list *new;

    curr = *head;
    new = (t_cmd_list *)malloc(sizeof(t_cmd_list));
    new->args = cmds; /*put the tokens here*/
    new->prev = NULL;
    new->next = NULL;
    if ((*head) == NULL)
    {
        (*head) = new;
        puts("setting the head");
        return;
    }
    puts("setting the nodes");
    while (curr->next)
        curr = curr->next;
    curr->next = new;
    new->prev = curr;
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
    s_split sp;
    
    //  use double pointer for declaring the struct ...
    prs->err.i = 0;
    new = malloc(sizeof(t_cmd_list));
    new->prev = NULL;
    new->next = NULL;
    new->beg = 1;
    new->end = 1;
    _initialize_vars(&sp);
    new->args = _split_tokens(&sp, line, ' ');
    new->command = ft_strdup(new->args[0]);
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
        // Fill the data of special tokens find a way to parse this tokens that has pipes and redirs in it..
}

char ret_spc(char buffer)
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
int is_special(char c)
{
    if (c == '\\' || c == '"' || c == '$')
        return 1;
    return 0;
}

char *_handle_backslash_(char *buffer)
{
    int i;
    char *tab;
    // int open = 0;
    int j;
    
    i = 0;
    j = 0;
    tab = (char *)malloc(sizeof(char) * (ft_strlen(buffer) + 1));
    printf("^%lu^\n", ft_strlen(buffer));
    while (i + 1 < (int)ft_strlen(buffer))
    {
        if (buffer[i] == '"')
        {
            tab[j] = buffer[i];
            i++;
            j++;
            while (buffer[i] != '"')
            {
                if (buffer[i] == '\\' && is_special(buffer[i + 1]))
                {
                    tab[j] = ret_spc(buffer[i + 1]);
                    j++;
                    i+=2;
                    continue;
                }
                tab[j] = buffer[i];
                j++;
                i++;
                printf("*%d-%d*,\n", j, (i + 1));
            }
            tab[j] = buffer[i];
            j++;
            i++;
        }
        else
        {
            tab[j] = buffer[i];
            i++;
            j++;
        }
        // Try to figure out the algorithm behind this one and test with bash not zsh AHOOOO
    }
    tab[j] = '\0';
    return (tab);
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

void _start_parsing(char *line, ms_p *prs, t_cmd_list **head)
{
    s_split sp;
    // int j;
    int i;
    t_cmd_list *curr;
    
    // curr = *head;
    _initialize_vars(&sp);
    if (parse(ft_strtrim(line, " \t\v\n"), prs))
        _raise_an_exception();
    else
    {
        prs->sc_cmds = _split_tokens(&sp, line, ';');
        i = -1;
        while (prs->sc_cmds[++i])
        {

            // if (in(prs->sc_cmds[i], '"'))
            //     prs->sc_cmds[i] = _handle_backslash_(prs->sc_cmds[i]);
            if (prs->sc_cmds[i] && prs->sc_cmds[i][0])
            {
                printf("--|%s|--\n", prs->sc_cmds[i]);
                _copy_tokens_data_(prs->sc_cmds[i], prs, head);
            }
            curr = (*head);
            while (curr)
            {
                printf("{%s}\n", curr->args[0]);
                curr = curr->next;
            }
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
            _free_all_(prs, head);
        }
    }
}