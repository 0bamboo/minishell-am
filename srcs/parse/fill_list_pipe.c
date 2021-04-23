/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_list_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 22:53:32 by abdait-m          #+#    #+#             */
/*   Updated: 2021/04/22 22:53:32 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void _fill_pipe_arg_(t_mp *prs, t_cmd_list **curr, char **args, char **files)
{
    int i;
    int j;

    i = -1;
    j = -1;
    (*curr)->args = malloc(sizeof(char *) * (prs->len + 1));
    while (args[++i])
        (*curr)->args[i] = ft_strdup(args[i]);
    (*curr)->redir = i;
    while (files[++j])
        (*curr)->args[i++] = ft_strdup(files[j]);
    (*curr)->args[i] = NULL;
    i = -1;
    while ((*curr)->args[++i])
        (*curr)->args[i] = _handle_backslash_(prs, (*curr)->args[i]);
}

void    _fill_list_for_pipe_args_(t_mp *prs, t_cmd_list **head, char **args, char **files)
{
    t_cmd_list *new;

    new = malloc(sizeof(t_cmd_list));
    new->next = NULL;
    new->nbrpipe = prs->nbrpipe;
    new->command = ft_strdup(args[0]);
    _fill_pipe_arg_(prs, &new, args, files);
    if ((*head) == NULL)
        (*head) = new;
    else
    {
        while ((*head)->next)
            (*head) = (*head)->next;
        (*head)->next = new;
    }
}