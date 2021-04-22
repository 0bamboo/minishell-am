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

#include "../includes/minishell.h"

void _count_token_length_2_(t_mp *prs)
{
    prs->count++;
    while (prs->buffer[prs->j] && prs->buffer[prs->j] != ' ' && prs->buffer[prs->j] != '>' && prs->buffer[prs->j] != '<')
    {
        if (prs->buffer[prs->j] == '"')
        {
            prs->j++;
            while (prs->buffer[prs->j] && prs->buffer[prs->j] != '"')
            {
                if (prs->buffer[prs->j] == '\\')
                {
                    prs->j += 2;
                    continue;
                }
                prs->j++;
            }
        }
        else if (prs->buffer[prs->j] == '\'')
            while (prs->buffer[++prs->j] && prs->buffer[prs->j] != '\'');
        prs->j++;
    }
    prs->j--;
}

int _count_token_length_(t_mp *prs)
{

    prs->j = -1;
    prs->count = 0;
    while (prs->buffer[++prs->j])
    {
        if (prs->buffer[prs->j] == ' ')
            continue;
        else if (prs->buffer[prs->j] == '>' || prs->buffer[prs->j] == '<')
        {
            prs->count++;
            if ( prs->buffer[prs->j + 1] ==  '>')
                prs->j++;
        }
        else
            _count_token_length_2_(prs);
    }
    return (prs->count);
}

int     _size_of_arg_(char *buffer, int i)
{
    // int i;
    int counter;

    // i = 0;
    counter = 0;
    while (buffer[i] && buffer[i] == ' ')
        i++;
    while (buffer[i])
    {
        if (buffer[i] == '"')
        {
            i++;
            counter++;
            while (buffer[i] && buffer[i] != '"')
            {
                if (buffer[i] == '\\')
                {
                    counter += 2;
                    i += 2;
                    continue;
                }
                i++;
                counter++;
            }
        }
        else if (buffer[i] == '\'')
        {
            counter++;
            i++;
            while (buffer[i] && buffer[i] != '\'')
            {
                counter++;
                i++;
            }
        }
        if (buffer[i] == ' ' || buffer[i] == '>' || buffer[i] == '<')
            break;
        i++;
        counter++;
    }
    return (counter);
}

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

void _fill_list_for_normal_args_(t_mp *prs, char **args, char **files)
{
    t_cmd_list *curr;
    int     i;
    int     j;
    
    curr = malloc(sizeof(t_cmd_list));
    // curr = prs->head;
    curr->nbrpipe = 0;
    curr->next = NULL;
    if (args[0])
        curr->command = ft_strdup(args[0]);
    curr->args = malloc(sizeof(char *) * (prs->len + 1));
    i = -1;
    // puts("im here");
    while (args[++i])
        curr->args[i] = ft_strdup(args[i]);
    j = -1;
    curr->redir = i;
    printf("redir = :%d:\n", curr->redir);
    while (files[++j])
        curr->args[i++] = ft_strdup(files[j]);
    curr->args[i] = NULL;
    i = -1;
    while (curr->args[++i])
        curr->args[i] = _handle_backslash_(prs, curr->args[i]);
    puts("");
    if (i == prs->len)
        puts("YAAAAY");
    prs->head = curr;
    // puts(curr->command);
}

void _copy_files_(t_mp *prs)
{
    if (prs->array[prs->i][1] == '>')
    {
        prs->files[prs->j++] = ft_strdup(">>");
        prs->files[prs->j++] = ft_strdup(prs->array[++prs->i]);
        prs->i++;
    }
    else if (prs->array[prs->i][0] == '<')
    {
        prs->files[prs->j++] = ft_strdup("<");
        prs->files[prs->j++] = ft_strdup(prs->array[++prs->i]);
        prs->i++;
    }
    else
    {
        prs->files[prs->j++] = ft_strdup(">");
        prs->files[prs->j++] = ft_strdup(prs->array[++prs->i]);
        prs->i++;
    }
}

void        _fix_the_order_(t_mp *prs)
{
    int arg;

    prs->j = 0;
    arg = 0;
    prs->i = 0;
    prs->args = malloc(sizeof(char *) * (prs->len + 1));
    prs->files = malloc(sizeof(char *) * (prs->len + 1));
    while (prs->array[prs->i])
    {
        if (prs->array[prs->i][0] == '>' || prs->array[prs->i][0] == '<')
            _copy_files_(prs);
        else
            prs->args[arg++] = ft_strdup(prs->array[prs->i++]);
    }
    prs->args[arg] = NULL;
    prs->files[prs->j] = NULL;
}

void    _copy_redirs_(t_mp *prs)
{
    if (prs->buffer[prs->i + 1] == '>')
    {
        prs->array[prs->size++] = ft_strdup(">>");
        prs->i += 2;
    }
    else if (prs->buffer[prs->i] == '<')
    {
        prs->array[prs->size++] = ft_strdup("<");
        prs->i++;
    }
    else
    {
        prs->array[prs->size++] = ft_strdup(">");
        prs->i++;
    }
}

void _copy_args_with_dq_(t_mp *prs)
{
    prs->array[prs->size][prs->j++] = prs->buffer[prs->i++];
    while (prs->buffer[prs->i] && prs->buffer[prs->i] != '"')
    {
        if (prs->buffer[prs->i] == '\\')
        {
            prs->array[prs->size][prs->j++] = prs->buffer[prs->i++];
            prs->array[prs->size][prs->j++] = prs->buffer[prs->i++];
            continue;
        }
        prs->array[prs->size][prs->j++] = prs->buffer[prs->i++];
    }
    prs->array[prs->size][prs->j++] = prs->buffer[prs->i++];
}

void _copy_args_with_sq_(t_mp *prs)
{
    prs->array[prs->size][prs->j++] = prs->buffer[prs->i++];
    while (prs->buffer[prs->i] && prs->buffer[prs->i] != '\'')
        prs->array[prs->size][prs->j++] = prs->buffer[prs->i++];
    prs->array[prs->size][prs->j++] = prs->buffer[prs->i++];
}

void _handle_normal_args_2_(t_mp *prs)
{
    int l = _size_of_arg_(prs->buffer, prs->i);
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
    int     len;
    // echo "ls"hello> file >hello

    prs->i = 0;
    // prs->head = malloc(sizeof(t_cmd_list));
    prs->buffer = tmp;
    len = _count_token_length_(prs);
    prs->size = 0;
    prs->array = malloc(sizeof(char *) * (len + 1));
    while (prs->buffer[prs->i] && prs->size < len)
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
    prs->len = len;
    _fix_the_order_(prs);
    _free_tab_(prs->array);
}

void _fill_first_node_(t_mp *prs, char **args, char **files)
{
    t_cmd_list *new;
    int j = -1;
    int i =-1;
    
    new = malloc(sizeof(t_cmd_list));
    new->nbrpipe = prs->nbrpipe;
    if (args[0])
        new->command = ft_strdup(args[0]);
    new->args = malloc(sizeof(char *) * (prs->len + 1));
    i = -1;
    while (args[++i])
        new->args[i] = ft_strdup(args[i]);
    new->redir = i;
    printf("redir = :%d:\n", new->redir);
    while (files[++j])
        new->args[i++] = ft_strdup(files[j]);
    i = -1;
    while (new->args[++i])
        new->args[i] = _handle_backslash_(prs, new->args[i]);
    new->next = NULL;
    prs->head = new;
}



void    _fill_list_for_pipe_args_(t_mp *prs, t_cmd_list **head, char **args, char **files)
{
    t_cmd_list *new;
    int i = -1;
    int j = -1;

    new = malloc(sizeof(t_cmd_list));
    new->next = NULL;
    new->nbrpipe = prs->nbrpipe;
    new->command = ft_strdup(args[0]);
    new->args = malloc(sizeof(char *) * (prs->len + 1));
    i = -1;
    while (args[++i])
        new->args[i] = ft_strdup(args[i]);
    new->redir = i;
    while (files[++j])
        new->args[i++] = ft_strdup(files[j]);
    new->args[i] = NULL;
    i = -1;
    while (new->args[++i])
        new->args[i] = _handle_backslash_(prs, new->args[i]);
    if ((*head) == NULL)
        (*head) = new;
    else
    {
        while ((*head)->next)
            (*head) = (*head)->next;
        (*head)->next = new;
    }
}