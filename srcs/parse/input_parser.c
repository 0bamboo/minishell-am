/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 18:38:31 by abdait-m          #+#    #+#             */
/*   Updated: 2021/04/23 00:03:50 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


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


void _if_pipe_dq_(t_mp *prs, int index)
{
    prs->i++;
    while (prs->cmds[index][prs->i] && prs->cmds[index][prs->i] != '"')
    {
        if (prs->cmds[index][prs->i] == '\\')
        {
            prs->i += 2;
            continue;
        }
        prs->i++;
    }
}


int     _if_pipe_(t_mp *prs, int index)
{
    // int count;

    prs->i = -1;
    prs->nbrpipe = 0;
    while (prs->cmds[index][++prs->i])
    {
        if (prs->cmds[index][prs->i] == '"')
            _if_pipe_dq_(prs, index);
        else if (prs->cmds[index][prs->i] == '\'')
            while (prs->cmds[index][++prs->i] && prs->cmds[index][prs->i] != '\'');
        else if (prs->cmds[index][prs->i] == '|')
            prs->nbrpipe++;
    }
    if (prs->nbrpipe)
        return (1);
    return (0);
}


void        _handle_pipe_args_(t_mp *prs)
{
    int     i;
    t_cmd_list *curr;

    curr = malloc(sizeof(t_cmd_list));
    curr = NULL;
    i = -1;
    while (prs->pipe[++i])
    {
        _handle_normal_args_(prs, prs->pipe[i]);
        _fill_list_for_pipe_args_(prs, &curr, prs->args, prs->files);
        if (i == 0)
            prs->head = curr;
        _free_tab_(prs->files);
    }
    _free_tab_(prs->args);
}

void        _copy_tokens_data_(t_mp *prs, int index)
{
    prs->head = malloc(sizeof(t_cmd_list));
    prs->head = NULL;
    if (_if_pipe_(prs, index))
    {
        prs->pipe = _split_tokens(prs->sp, prs->cmds[index], '|');
        _handle_pipe_args_(prs);
        // handle pipe ....
    }
    else
    {
        _handle_normal_args_(prs, prs->cmds[index]);
        _fill_list_for_normal_args_(prs, prs->args, prs->files);
        _free_tab_(prs->args);
        _free_tab_(prs->files);
        
    }
}



void _start_parsing(char *line, t_mp *prs)
{
    // t_sp *sp;
    int i;
    // prs->head = malloc(sizeof(t_cmd_list));
	// char *tmp;
    
	line = ft_strtrim(line, " \t\v\n\r");
    if (_handle_syntax_errors(line, prs))
        _raise_an_exception();
    else
    {
		prs->cmds = _split_tokens(prs->sp, line, ';');
        i = -1;
        // echo $$0$?"hi agina \\\$0 $$9abdennacer \\$?$?$??? hi \" \\\" out"
        while (prs->cmds[++i])
        {
            prs->cmds[i] = _get_env_vars_(prs->cmds[i], prs);
            _copy_tokens_data_(prs, i);
            int j = -1;
            while (prs->head)
            {
                printf("---pipe list----> |%d| |%s|", prs->head->nbrpipe, prs->head->command);
                puts("");
                j =-1;
                while (prs->head->args[++j])
                    printf("---------> pipe args = |%s|\n", prs->head->args[j]);
                prs->head = prs->head->next;
            }
            printf("pipe counter == |%d|\n", prs->nbrpipe);
        }
        i = -1;
        while (prs->cmds[++i])
            printf("---> |%s|\n", prs->cmds[i]);
    }
}