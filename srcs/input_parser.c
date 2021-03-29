/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 18:38:31 by abdait-m          #+#    #+#             */
/*   Updated: 2021/03/29 16:53:07 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int     _check_special_chars_(char check, char check_nx, ms_p *prs)
{
    if ((check == '|' || check == '>' || check == '\\' || check == '<') && check_nx == '\0')
        return (1);
    if (check == ';' && check_nx == '\0' && prs->err.len <= 2)
        return 1;
    if (check == ';' && prs->err.tmp == ';' && prs->err.dq == 0 && prs->err.sq == 0)
        return 1;
    return 0;
}

int     _char_in_tab_(char c, char tab[3])
{
    if (c == tab[0] || c == tab[1] || c == tab[2])
        return 1;
    return 0;
}
// fix spc space spc????????????????????????

int  _check_4_repeated_spc_(char *buff)
{
    int countredir;
    int countpp;

    countredir = 0;
    countpp = 0;
    while (*buff)
    {
        if (_char_in_tab_(*buff, "|<>"))
            countredir++;
        else
            countredir = 0;
        if (countredir == 3 || countpp == 2)
            return 1;
        buff++;
    }
    return 0;
}

int     _check_near_spc_(char *buff)
{
    int     spc;
    
    spc = 0;
    while (*buff)
    {
        if (*buff == '>' || *buff == '<' || *buff == '|')
            spc++;
        else if (*buff == ' ' || *buff == '\t')
        {
            buff++;
            continue;
        }
        else
            spc = 0;
        buff++;
        if (spc == 2)
            return 1;
    }
    return 0;
}

int _check_parsing_errors(char *line, ms_p *prs)
{
    int ret;

    ret = 0;

    prs->err.i = -1;
    prs->err.sq = 0;
    prs->err.dq = 0;
    prs->err.countsq = 0;
    prs->err.countdq = 0;
    prs->err.tmp = '\0';
    line = ft_strtrim(line, " \t");
    prs->err.len = ft_strlen(line);
    while (line[++prs->err.i])
    {
        if (line[0] == ';' || line[0] == '|' || ret)
            return 1;
        if (_check_special_chars_(line[prs->err.i], line[prs->err.i + 1], prs))
            return 1;
        if (line[prs->err.i] == '"' && prs->err.dq == 0 && prs->err.sq == 0)
        {
            prs->err.countdq++;
            prs->err.dq = 1;
        }
        else if (line[prs->err.i] == '"' && prs->err.dq == 1)
        {
            prs->err.countdq--;
            prs->err.dq = 0;
        }
        if (line[prs->err.i] == '\'' && prs->err.sq == 0 && prs->err.dq == 0)
        {
            prs->err.countsq++;
            prs->err.sq = 1;
        }
        else if (line[prs->err.i] == '\'' && prs->err.sq == 1)
        {
            prs->err.countsq--;
            prs->err.sq = 0;
        }
        if (_char_in_tab_(line[prs->err.i], "<>|") && !prs->err.dq && !prs->err.sq)
            ret = _check_4_repeated_spc_(line + prs->err.i) + _check_near_spc_(line + prs->err.i);
        if (prs->err.tmp == '\\' && line[prs->err.i] == '"' && prs->err.sq == 0 && prs->err.dq ==  0)
            return (1);
        prs->err.tmp = line[prs->err.i];
    }
    return (prs->err.countsq + prs->err.countdq);
}


void        _raise_an_exception()
{
    printf("Parsing Error !!\n");
}

void        _initialize_vars(s_split *ps)
{
    ps->check_dq = 0;
    ps->check_sq = 0;
    ps->i = 0;
    
}



int         _check_for_pipe(ms_p *prs, int current)
{
    int     i;
    int     q;
    int     dq;

    i = 0;
    q = 0;
    dq = 0;
    while (prs->sc_cmds[current][i])
    {
        if (prs->sc_cmds[current][i] == '"' && dq == 0 && q == 0)
            dq = 1;
        else if (prs->sc_cmds[current][i] == '\'' && q == 0 && dq == 0)
            q = 1;
        else if (prs->sc_cmds[current][i] == '|' && dq == 0 && q == 0)
            return i;
        else if (prs->sc_cmds[current][i] == '"' && dq == 1)
            dq = 0;
        else if (prs->sc_cmds[current][i] == '\'' && q == 1)
            q = 0;
        i++;
    }
    return (0);
}

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
    // if ((*head)->cmd)
    //     free((*head)->cmd);
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
    int i;

    i = -1;
    _free_all_tokens(head);
    if (prs->sc_cmds)
    {
        while (prs->sc_cmds[++i])
                free(prs->sc_cmds[i]);
        free(prs->sc_cmds);
        prs->sc_cmds = NULL;
    }
    
}


void _start_parsing(char *line, ms_p *prs, t_cmd_list **head)
{
    s_split sp;
    // int j;
    int i;
    t_cmd_list *curr;
    
    // curr = *head;
    _initialize_vars(&sp);
    if (_check_parsing_errors(line, prs))
        _raise_an_exception();
    else 
    {
        prs->sc_cmds = _split_tokens(&sp, line, ';');
        i = 0;
        // j = 0;
        // prs->space_cmd = (char ***)malloc(sizeof(char **) * (sp.size));
        while (prs->sc_cmds[i])
        {
            printf("--|%s|--\n", prs->sc_cmds[i]);
            // create a function that checks if there is a pipe or redirection in every token
            prs->sp_cmds = _split_tokens(&sp, prs->sc_cmds[i], ' ');
            _push_back_tokens(head, prs->sp_cmds);
            i++;
        }
        curr = (*head);
        while (curr)
        {
            printf("dll = -> |%s| <-\n", curr->args[0]);   
            puts("1");
            curr = curr->next;
        }
        _free_all_(prs, head);
    }
}