/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majermou <majermou@students.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 13:12:19 by majermou          #+#    #+#             */
/*   Updated: 2021/05/10 13:18:58 by majermou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	save_fd(t_envlist *envlist)
{
	envlist->fd = malloc(sizeof(int) * 3);
	envlist->fd[0] = dup(0);
	envlist->fd[1] = dup(1);
	envlist->fd[2] = dup(2);
}

void	restore_fd(t_envlist *envlist)
{
	dup2(envlist->fd[0], 0);
	dup2(envlist->fd[1], 1);
	dup2(envlist->fd[2], 2);
	free(envlist->fd);
	envlist->fd = NULL;
}

int	removeFromline(t_envlist *envlist)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = envlist->line;
	envlist->line = malloc(ft_strlen(envlist->line) * sizeof(char));
	while (tmp[i + 1])
	{
		envlist->line[i] = tmp[i];
		i++;
	}
	envlist->line[i] = '\0';
	free(tmp);
	return (0);
}

char	*get_home_path(char **args, char **envp)
{
	struct stat		buf;
	char			**arr;
	char			*tmp;
	char			*path;

	arr = NULL;
	while (*envp && strncmp(*envp, "PATH=", 5))
		envp++;
	if (*envp)
		arr = ft_split(*envp + 5, ':');
	while (*arr)
	{
		path = ft_strjoin(*arr++, "/");
		tmp = path;
		path = ft_strjoin(path, *args);
		free(tmp);
		if (!stat(path, &buf))
		{
			while (*arr)
				free(*arr++);
			return (path);
		}
		free(path);
	}
	return (NULL);
}

int	addTohistory(t_envlist *envlist)
{
	char		**tmp;
	int			lenght;
	int			i;
	int			k;

	lenght = 0;
	tmp = envlist->history;
	while (tmp && tmp[lenght])
		lenght++;
	envlist->history = malloc((lenght + 2) * sizeof(char *));
	if (!envlist->history)
		return (1);
	envlist->history[0] = ft_strdup(envlist->line);
	i = 1;
	k = 0;
	while (tmp && tmp[k])
		envlist->history[i++] = ft_strdup(tmp[k++]);
	envlist->history[i] = NULL;
	k = 0;
	while (tmp && tmp[k])
		free(tmp[k++]);
	free(tmp);
	return (0);
}
