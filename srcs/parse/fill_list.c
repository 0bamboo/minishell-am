/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 23:38:08 by abdait-m          #+#    #+#             */
/*   Updated: 2021/04/21 23:38:08 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



void _free_tab_(char **buffer)
{
    int     i;
    
    i = -1;
    if (buffer)
    {
        if (buffer[++i])
            while (buffer[i])
                free(buffer[i++]);
        free(buffer);
        buffer = NULL; 
    }
}

void _handle_normal_args_2_(t_mp *prs)
{
    int l = _size_of_arg_(prs, prs->buffer, prs->i);
    prs->array[prs->size] = malloc(sizeof(char) * (l + 1));
    prs->j = 0;
    //echo >file "hiag"'hi'hi >file "hi"
    while (prs->buffer[prs->i])
    {
        if (prs->buffer[prs->i] == '>' || prs->buffer[prs->i] == '<' || prs->buffer[prs->i] == ' ')
            break;
        else if (prs->buffer[prs->i] == '"')
            _copy_args_with_dq_(prs);
        else if (prs->buffer[prs->i] == '\'')
            _copy_args_with_sq_(prs);
        else
            prs->array[prs->size][prs->j++] = prs->buffer[prs->i++];
    }
    prs->array[prs->size++][prs->j] = '\0';
}

void _handle_normal_args_(t_mp *prs, char *tmp)
{
    // int     len;
    // echo "ls"hello> file >hello

    // prs->head = malloc(sizeof(t_cmd_list));
    prs->buffer = tmp;
    prs->len = _count_token_length_(prs);
    prs->size = 0;
    prs->array = malloc(sizeof(char *) * (prs->len + 1));
    prs->i = 0;
    while (prs->buffer[prs->i] && prs->size < prs->len)
    {
        if (prs->buffer[prs->i] == '>' || prs->buffer[prs->i] == '<')
            _copy_redirs_(prs);
        else if (prs->buffer[prs->i] == ' ')
        {
            prs->i++;
            continue;
        }
        else
            _handle_normal_args_2_(prs);
    }
    prs->array[prs->size] = NULL;
    _fix_the_order_(prs);
    _free_tab_(prs->array);
}

void _fill_normal_args_(t_mp *prs, t_cmd_list **curr, char **args, char **files)
{
    int i;
    int j;

    i = -1;
    (*curr)->args = malloc(sizeof(char *) * (prs->len + 1));
    while (args[++i])
        (*curr)->args[i] = ft_strdup(args[i]);
    j = -1;
    (*curr)->redir = i;
    printf("redir = :%d:\n", (*curr)->redir);
    while (files[++j])
        (*curr)->args[i++] = ft_strdup(files[j]);
    (*curr)->args[i] = NULL;
    i = -1;
    while ((*curr)->args[++i])
        (*curr)->args[i] = _handle_backslash_(prs, (*curr)->args[i]);
}

void _fill_list_for_normal_args_(t_mp *prs, char **args, char **files)
{
    t_cmd_list *curr;
    // int     i;
    // int     j;
    
    curr = malloc(sizeof(t_cmd_list));
    // curr = prs->head;
    curr->nbrpipe = 0;
    curr->next = NULL;
    if (args[0])
        curr->command = ft_strdup(args[0]);
    _fill_normal_args_(prs, &curr,args, files);
    // curr->args = malloc(sizeof(char *) * (prs->len + 1));
    // i = -1;
    // // puts("im here");
    // while (args[++i])
    //     curr->args[i] = ft_strdup(args[i]);
    // j = -1;
    // curr->redir = i;
    // printf("redir = :%d:\n", curr->redir);
    // while (files[++j])
    //     curr->args[i++] = ft_strdup(files[j]);
    // curr->args[i] = NULL;
    // i = -1;
    // while (curr->args[++i])
    //     curr->args[i] = _handle_backslash_(prs, curr->args[i]);
    puts("");
    // if (i == prs->len)
    //     puts("YAAAAY");
    prs->head = curr;
    // puts(curr->command);
}
