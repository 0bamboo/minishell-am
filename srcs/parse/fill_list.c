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

void	_free_tab_(char **buffer)
{
	int	i;

	i = -1;
	if (buffer)
	{
		while (buffer[++i])
		{
			free(buffer[i]);
			buffer[i] = NULL;
		}
		free(buffer);
		buffer = NULL;
	}
}

void	_handle_normal_args_2_(t_mp *prs)
{
	int	l;

	l = _size_of_arg_(prs, prs->buff, prs->i);
	prs->array[prs->size] = malloc(sizeof(char) * (l + 1));
	if (!prs->array[prs->size])
		return ;
	prs->j = 0;
	while (prs->buff[prs->i])
	{
		if (prs->buff[prs->i] == '>' || prs->buff[prs->i] == '<'
			|| prs->buff[prs->i] == ' ')
			break ;
		else if (prs->buff[prs->i] == '"')
			_copy_args_with_dq_(prs);
		else if (prs->buff[prs->i] == '\'')
			_copy_args_with_sq_(prs);
		else
			prs->array[prs->size][prs->j++] = prs->buff[prs->i++];
	}
	prs->array[prs->size++][prs->j] = '\0';
}

void	_handle_normal_args_(t_mp *prs, char *tmp)
{
	prs->buff = tmp;
	prs->len = _count_token_length_(prs);
	prs->size = 0;
	prs->array = malloc(sizeof(char *) * (prs->len + 1));
	if (!prs->array)
		return ;
	prs->i = 0;
	while (prs->buff[prs->i] && prs->size < prs->len)
	{
		if (prs->buff[prs->i] == '>' || prs->buff[prs->i] == '<')
			_copy_redirs_(prs);
		else if (prs->buff[prs->i] == ' ')
		{
			prs->i++;
			continue ;
		}
		else
			_handle_normal_args_2_(prs);
	}
	prs->array[prs->size] = NULL;
	_fix_the_order_(prs);
	_free_tab_(prs->array);
}

void	_fill_normal_args_(t_mp *prs, t_cmd_list **curr,
char **args, char **files)
{
	int	i;
	int	j;

	i = -1;
	(*curr)->args = malloc(sizeof(char *) * (prs->len + 1));
	if (!(*curr)->args)
		return ;
	while (args[++i])
		(*curr)->args[i] = ft_strdup(args[i]);
	j = -1;
	if (files[0])
		(*curr)->redir = i;
	while (files[++j])
		(*curr)->args[i++] = ft_strdup(files[j]);
	(*curr)->args[i] = NULL;
	i = -1;
	while ((*curr)->args[++i])
		(*curr)->args[i] = _handle_backslash_(prs, (*curr)->args[i]);
	_free_tab_(args);
	_free_tab_(files);
}

void	_fill_list_for_normal_args_(t_mp *prs, char **args, char **files)
{
	t_cmd_list	*curr;

	curr = malloc(sizeof(t_cmd_list));
	if (!curr)
		return ;
	curr->nbrpipe = 0;
	curr->redir = -1;
	curr->iterator = 0;
	curr->next = NULL;
	_fill_normal_args_(prs, &curr, args, files);
	prs->head = curr;
}
