/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 13:12:19 by majermou          #+#    #+#             */
/*   Updated: 2021/05/10 18:39:54 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	check_speCase(char **args, struct stat buf, char **path)
{
	*path = NULL;
	if (!ft_strncmp(*args, "~", 2))
	{
		free(*args);
		*args = getenv("HOME");
	}
	if (!stat(*args, &buf))
	{
		if (opendir(*args))
		{
			printf("minishell: %s: is a directory\n", *args);
			exit(126);
		}
		*path = ft_strdup(*args);
		return (1);
	}
	else
	{
		printf("minishell: %s: No such file or directory\n", *args);
		exit(127);
	}
	return (0);
}

char	*checking(char **args, char **arr, struct stat buf)
{
	char	*path;
	char	*tmp;
	int		j;

	j = 0;
	while (arr[j])
	{
		path = ft_strjoin(arr[j], "/");
		tmp = path;
		path = ft_strjoin(path, *args);
		free(tmp);
		if (!stat(path, &buf))
		{
			while (arr[j])
				free(arr[j++]);
			free(arr);
			return (path);
		}
		free(path);
		free(arr[j++]);
	}
	return (NULL);
}

char	*get_home_path(char **args, char **envp)
{
	struct stat		buf;
	char			**arr;
	char			*path;

	arr = NULL;
	if (!ft_strncmp(*args, "/", 1) || !ft_strncmp(*args, "./", 2)
		|| !ft_strncmp(*args, "~", 1))
		if (check_speCase(args, buf, &path))
			return (path);
	while (*envp && ft_strncmp(*envp, "PATH=", 5))
		envp++;
	if (!*envp)
		check_speCase(args, buf, &path);
	arr = ft_split(*envp + 5, ':');
	path = checking(args, arr, buf);
	if (path)
		return (path);
	free(arr);
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
