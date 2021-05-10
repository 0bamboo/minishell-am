/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majermou <majermou@students.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 13:07:49 by majermou          #+#    #+#             */
/*   Updated: 2021/05/10 13:07:50 by majermou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	array_lenght(char **arr)
{
	int		lenght;

	lenght = 0;
	while (arr[lenght])
		lenght++;
	return (lenght);
}

int	is_valid_id(char *id)
{
	int		i;

	if (!ft_isalpha(id[0]))
		return (1);
	i = 1;
	while (id[i])
	{
		if (!ft_isalpha(id[i]) && !ft_isalnum(id[i]) && id[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	str_copying(char **dst, char *src, int index)
{
	dst[index] = (char *)malloc((ft_strlen(src) + 1) * sizeof(char));
	if (!dst[index])
	{
		cleanup(dst, index);
		return (1);
	}
	ft_strlcpy(dst[index], src, ft_strlen(src) + 1);
	return (0);
}

int	rmfrom_envlist(t_envlist *envlist, char *rm_var)
{
	char		**ret;
	char		*str;
	int			i;
	int			j;

	ret = (char **)malloc(((array_lenght(envlist->vars) + 1) * sizeof(char *)));
	if (!ret)
		return (1);
	i = 0;
	j = 0;
	str = ft_strjoin(rm_var, "=");
	while (envlist->vars[i])
	{
		if (ft_strcmp(envlist->vars[i], rm_var)
			&& ft_strncmp(envlist->vars[i], str, ft_strlen(str)))
			if (str_copying(ret, envlist->vars[i], j++))
				return (1);
		i++;
	}
	ret[j] = NULL;
	free(str);
	cleanup(envlist->vars, array_lenght(envlist->vars));
	free(envlist->vars);
	envlist->vars = ret;
	return (0);
}

int	builtin_unset(t_cmd_list *cmd, t_envlist *envlist)
{
	int		i;
	int		ret;

	ret = 0;
	i = 1;
	while (cmd->args[i])
	{
		if (!is_valid_id(cmd->args[i]))
		{
			if (rmfrom_envlist(envlist, cmd->args[i]))
				return (1);
		}
		else
		{
			printf("minishell: unset: `%s': not a valid identifier\n",
				cmd->args[i]);
			ret = 1;
		}
		i++;
	}
	return (ret);
}
