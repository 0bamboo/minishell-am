/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majermou <majermou@students.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 13:06:55 by majermou          #+#    #+#             */
/*   Updated: 2021/05/10 13:06:56 by majermou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clean_cmdList(t_envlist *env)
{
	int			i;
	t_cmd_list	*tmp;

	while (env->head)
	{
		i = 0;
		if (env->head->args)
		{
			while (env->head->args && env->head->args[i])
				free(env->head->args[i++]);
			free(env->head->args);
		}
		tmp = env->head;
		env->head = env->head->next;
		free(tmp);
	}
}

void	freeing(t_envlist *envlist)
{
	int		i;

	if (envlist->prs->cmds)
	{
		i = -1;
		while (envlist->prs->cmds[++i])
			free(envlist->prs->cmds[i]);
		free(envlist->prs->cmds);
		envlist->prs->cmds = NULL;
	}
	free(envlist->prs->sp);
	free(envlist->prs);
}

void	cleaning(t_envlist *envlist)
{
	int		i;

	freeing(envlist);
	if (envlist->vars)
	{
		i = 0;
		while (envlist->vars[i])
			free(envlist->vars[i++]);
		free(envlist->vars);
	}
	if (envlist->history)
	{
		i = 0;
		while (envlist->history[i])
			free(envlist->history[i++]);
		free(envlist->history);
	}
	clean_cmdList(envlist);
	free(envlist);
}