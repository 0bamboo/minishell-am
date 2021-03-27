/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 18:38:31 by abdait-m          #+#    #+#             */
/*   Updated: 2021/03/27 15:45:23 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int _check_parsing_errors(char *line)
{
    int open_sq;
    int count_sq;
    int open_dq;
    int count_dq;
    int i;

    i = -1;
    open_sq = 0;
    open_dq = 0;
    count_sq = 0;
    count_dq = 0;
    while (line[++i])
    {
        if (line[i] == ';' && line[i + 1] == ';' && open_dq == 0 && open_sq == 0)
            return 1;
        if (line[i] == '"' && open_dq == 0 && open_sq == 0)
        {
            count_dq++;
            open_dq = 1;
        }
        else if (line[i] == '"' && open_dq == 1)
        {
            count_dq--;
            open_dq = 0;
        }
        if (line[i] == '\'' && open_sq == 0 && open_dq == 0)
        {
            count_sq++;
            open_sq = 1;
        }
        else if (line[i] == '\'' && open_sq == 1)
        {
            count_sq--;
            open_sq = 0;
        }
    }
    return (count_sq + count_dq);
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
    printf("#-%s-#\n", prs->sc_cmds[current]);
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

void        _push_back_tokens(p_list **head, char **cmds)
{
    p_list *curr;
    p_list *new;

    curr = *head;
    new = (p_list *)malloc(sizeof(p_list));
    new->args = cmds; /*put the tokens here*/
    // printf("|%s|,\n", new->args[0]);
    // printf("|%s|,\n", new->args[1]);
    if (curr == NULL)
    {
        new->prev = NULL;
        new->next = NULL;
        // new->args = malloc(sizeof(char *) * 100);
        (*head) = new;
        // puts("im in");
        return;
    }
    while (curr->next)
        curr = curr->next;
    curr->next = new;
    new->next = NULL;
    new->prev = curr;
    // puts("hi");
    // printf("|%s|,\n", new->args[0]);
    // add the data of the new node :
}

void        _free_all_tokens(p_list **head)
{
    p_list *curr;
    p_list *next;
    
    curr = *head;
    while (curr)
    {
        next = curr->next;
        free(curr);
        curr = next;
    }
}


void _start_parsing(char *line, ms_p *prs, p_list **head)
{
    s_split sp;
    int j;
    int i;
    p_list *curr;
    
    _initialize_vars(&sp);
    if (_check_parsing_errors(line))
        _raise_an_exception();
    else 
    {
        prs->sc_cmds = _split_tokens(&sp, line, ';');
        i = 0;
        j = 0;
        // prs->space_cmd = (char ***)malloc(sizeof(char **) * (sp.size));
        while (prs->sc_cmds[i])
        {
            // create a function that checks if there is a pipe or redirection in every token
            prs->sp_cmds = _split_tokens(&sp, prs->sc_cmds[i], ' ');
            if (_check_for_pipe(prs, i))
            {
                // in this section well need to figure out how to parse pipe and redir ...
                prs->pipe[j] = i;
                j++;
                _push_back_tokens(head, prs->sp_cmds);
            }
            else
                _push_back_tokens(head, prs->sp_cmds);
            i++;
        }
        // j = -1;
        // while (prs->pipe[++j])
        //     printf("/%d/\n", prs->pipe[j]);
        // write(1, "free time\n", 10);
        curr = *head;
        while (curr)
        {
            printf("dll = |**-%s-**|\n", curr->args[0]);
            curr = curr->next;
        }
        _free_all_tokens(head);
    }
}