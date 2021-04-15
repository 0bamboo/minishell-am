/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 18:38:31 by abdait-m          #+#    #+#             */
/*   Updated: 2021/04/15 13:45:11 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"




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
    _free_all_tokens(head);
    prs->err.i = 0;
}

int     _check_for_special_chars_(char *buff)
{
    int i;

    i = 0;
    while (buff[i])
    {
        if (buff[i] == '"')
            while (buff[++i] && buff[i] != '"');
        else if (buff[i] == '\'')
            while (buff[++i] && buff[i] != '\'');
        if (_char_in_tab_(buff[i], "><|"))
            return 1;
        i++;
    }
    return 0;
}


void _push_back_normal_tokens_(t_cmd_list **head, ms_p *prs)
{
    t_cmd_list *curr;
    t_cmd_list *new;
    
    //  use double pointer for declaring the struct ...
    prs->err.i = 0;
    new = malloc(sizeof(t_cmd_list));
    new->prev = NULL;
    new->next = NULL;
    new->beg = 1;
    new->end = 1;
    if (!(*head))
        (*head) = new;
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
    char **tmp;
    int i;
    s_split sp;

    i = 0;
    prs->sp = &sp;
    // prs->count = 0;
    // prs->sp = malloc(sizeof(s_split));
    tmp = NULL;
    *head = NULL;
    puts("im in copy");
    // if (!_check_for_special_chars_(token))
    tmp = _split_tokens(prs->sp, token, ' '); // _push_back_normal_tokens_(head, prs);  
    // else
    //     puts("special tokens");
    puts("w hi");
    // printf("tmp[%d]=%s", 1,tmp[1]);
    while (tmp[i])
    {
        printf("pushing  = |%s|\n", tmp[i]);
        i++;
    }
    // free(token);
    // token = NULL;
    // i = 0;
    // while (tmp[i])     
    //     free(tmp[i]);
    // free(tmp);
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
    s_split *sp;
    int i;
    
    sp = malloc(sizeof(s_split));
    _initialize_vars(sp);
    if (_handle_syntax_errors(ft_strtrim(line, " \t\v\n\r"), prs))
        _raise_an_exception();
    else
    {
        prs->sc_cmds = _split_tokens(sp, line, ';');
        i = -1;
        printf("size = |%d|\n", sp->size);
        while (prs->sc_cmds[++i])
        {
            prs->sc_cmds[i] = _get_env_vars_(prs->sc_cmds[i], prs);
            if (in(prs->sc_cmds[i], '"'))
                prs->sc_cmds[i] = _handle_backslash_(prs, prs->sc_cmds[i]);
            if (prs->sc_cmds[i])
                _copy_tokens_data_(prs->sc_cmds[i], prs, head);
            printf(" im out {global}   ---> : |%s|\n", prs->global);
        }
        // i = -1;
        // while (prs->sc_cmds[++i])
        //     free(prs->sc_cmds[i]);
        // free(prs->sc_cmds);
    }
    // free(sp);
}