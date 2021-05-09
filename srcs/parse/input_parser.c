/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 18:38:31 by abdait-m          #+#    #+#             */
/*   Updated: 2021/05/09 15:48:40 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	_if_pipe_dq_(t_mp *prs, int index)
{
	prs->i++;
	while (prs->cmds[index][prs->i] && prs->cmds[index][prs->i] != '"')
	{
		if (prs->cmds[index][prs->i] == '\\')
		{
			prs->i += 2;
			continue ;
		}
		prs->i++;
	}
}

int	_if_pipe_(t_mp *prs, int index)
{
	prs->i = -1;
	prs->nbrpipe = 0;
	while (prs->cmds[index][++prs->i])
	{
		if (prs->cmds[index][prs->i] == '"')
			_if_pipe_dq_(prs, index);
		else if (prs->cmds[index][prs->i] == '\'')
			while (prs->cmds[index][++prs->i]
				&& prs->cmds[index][prs->i] != '\'')
				;
		else if (prs->cmds[index][prs->i] == '|')
			prs->nbrpipe++;
	}
	if (prs->nbrpipe)
		return (1);
	return (0);
}

void	_handle_pipe_args_(t_mp *prs)
{
	int			i;
	t_cmd_list	*curr;

	curr = malloc(sizeof(t_cmd_list));
	curr = NULL;
	i = -1;
	while (prs->pipe[++i])
	{
		_handle_normal_args_(prs, prs->pipe[i]);
		prs->iter = i;
		_fill_list_for_pipe_args_(prs, &curr, prs->args, prs->files);
		if (i == 0)
			prs->head = curr;
	}
	free(prs->pipe);
	prs->pipe = NULL;
}

void	_copy_tokens_data_(t_mp *prs, int index)
{
	prs->head = malloc(sizeof(t_cmd_list));
	prs->head = NULL;
	if (_if_pipe_(prs, index))
	{
		prs->pipe = _split_tokens(prs->sp, prs->cmds[index], '|');
		_handle_pipe_args_(prs);
	}
	else
	{
		_handle_normal_args_(prs, prs->cmds[index]);
		_fill_list_for_normal_args_(prs, prs->args, prs->files);
	}
}

void	_start_parsing(char *line, t_mp *prs, t_envlist *env)
{
	int	i;

	line = ft_strtrim(line, " \t\v\n\r");
	if (_handle_syntax_errors(line, prs))
		_raise_an_exception();
	else
	{
		prs->cmds = _split_tokens(prs->sp, line, ';');
		i = -1;
		while (prs->cmds[++i])
		{
			prs->cmds[i] = _get_env_vars_(prs->cmds[i], prs, env);
			_copy_tokens_data_(prs, i);
			save_fd(env);
			env->status = execute_cmd(prs->head, env);
			prs->status = env->status;
			restore_fd(env);
		}
	}
}
