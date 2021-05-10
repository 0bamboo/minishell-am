/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majermou <majermou@students.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 13:06:55 by majermou          #+#    #+#             */
/*   Updated: 2021/05/10 16:02:38 by majermou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	shell_lvl(t_envlist *envlist)
{
	char	*tmp;
	char	*tmp1;
	int		shl;

	tmp = getenv("SHLVL");
	shl = ft_atoi(tmp);
	shl++;
	tmp1 = ft_itoa(shl);
	tmp = ft_strjoin("SHLVL=", tmp1);
	free(tmp1);
	rmfrom_envlist(envlist, "SHLVL");
	addto_envlist(envlist, tmp);
	rmfrom_envlist(envlist, "OLDPWD");
	free(tmp);
	envlist->fd = NULL;
	envlist->fds = NULL;
	envlist->pids = NULL;
}

void	cleanfds(t_envlist *envlist)
{
	if (envlist->fds)
		free(envlist->fds);
	if (envlist->pids)
		free(envlist->pids);
	if (envlist->fd)
		free(envlist->fd);
}

void	clean_cmdList(t_envlist *env)
{
	int			i;
	t_cmd_list	*tmp;

	while (env->head)
	{
		i = 0;
		if (env->head->args)
		{
			if (ft_strncmp(env->head->args[0], "cd", 2) || !env->head->args[1])
			{
				while (env->head->args && env->head->args[i])
					free(env->head->args[i++]);
				free(env->head->args);
			}
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
	cleanfds(envlist);
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
