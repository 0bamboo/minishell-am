/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majermou <majermou@students.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 13:07:55 by majermou          #+#    #+#             */
/*   Updated: 2021/05/10 13:07:56 by majermou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_equalkey(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i])
		return (0);
	return (1);
}

int	env_varsdup(t_envlist *envlist, char **envp)
{
	char	**ret;
	int		i;

	ret = (char **)malloc((array_lenght(envp) + 1) * sizeof(char *));
	if (!ret)
		return (1);
	i = 0;
	while (envp[i])
	{
		ret[i] = (char *)malloc((ft_strlen(envp[i]) + 1) * sizeof(char));
		if (!ret)
		{
			cleanup(ret, i);
			return (1);
		}
		ft_strlcpy(ret[i], envp[i], ft_strlen(envp[i]) + 1);
		i++;
	}
	ret[i] = NULL;
	envlist->vars = ret;
	return (0);
}

int	addto_envlist(t_envlist *envlist, char *new_var)
{
	char		**ret;
	int			i;
	int			j;
	int			random;

	ret = (char **)malloc((array_lenght(envlist->vars) + 2) * sizeof(char *));
	if (!ret)
		return (1);
	i = 0;
	j = 0;
	random = random_num_generator(array_lenght(envlist->vars));
	while (i < random)
		if (str_copying(ret, envlist->vars[i++], j++))
			return (1);
	if (str_copying(ret, new_var, j++))
		return (1);
	while (envlist->vars[i])
		if (str_copying(ret, envlist->vars[i++], j++))
			return (1);
	ret[j] = NULL;
	cleanup(envlist->vars, array_lenght(envlist->vars));
	free(envlist->vars);
	envlist->vars = ret;
	return (0);
}

int	search_var(t_envlist *envlist, char *var)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strjoin(var, "=");
	while (envlist->vars[i])
	{
		if (!ft_strcmp(envlist->vars[i], var)
			|| !ft_strncmp(envlist->vars[i], tmp, ft_strlen(tmp)))
		{
			free(tmp);
			return (i);
		}
		i++;
	}
	return (-1);
}

int	builtin_env(t_envlist *envlist)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (envlist->vars[i])
	{
		j = 0;
		while (envlist->vars[i][j] && envlist->vars[i][j] != '=')
			j++;
		if (envlist->vars[i][j])
			printf("%s\n", envlist->vars[i]);
		i++;
	}
	return (0);
}
