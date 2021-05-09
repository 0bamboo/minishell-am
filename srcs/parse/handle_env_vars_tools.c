/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_vars_tools.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 14:01:12 by abdait-m          #+#    #+#             */
/*   Updated: 2021/05/09 14:43:23 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	_isspec_(char c)
{
	if (c == '_' || c == '@' || c == '&' || c == '!' || c == '#')
		return (1);
	return (0);
}

void	_push_back_string_(char *buff, int index, char *fill, int size)
{
	int	i;

	i = -1;
	while (fill[++i] && size > 0)
	{
		buff[index++] = fill[i];
		size--;
	}
	free(fill);
	fill = NULL;
}

void	_env_var_counter_(t_mp *prs, t_envlist *env)
{
	int	size;

	prs->j = -1;
	while (env->vars[++prs->j])
	{
		if (!ft_strncmp(prs->temp, env->vars[prs->j], prs->count))
		{
			size = ft_strlen(env->vars[prs->j]) - prs->count;
			prs->counter += size;
			break ;
		}
	}
}

void	_env_var_copy_(t_mp *prs, t_envlist *env)
{
	int	size;
	int	i;

	size = 0;
	while (env->vars[++prs->j])
	{
		if (!ft_strncmp(prs->temp, env->vars[prs->j], prs->count))
		{
			size = ft_strlen(env->vars[prs->j]) - prs->count;
			prs->env = malloc(sizeof(char) * (size + 1));
			if (!prs->env)
				return ;
			break ;
		}
	}
	i = 0;
	if (size)
	{
		while (env->vars[prs->j][prs->count] && i < size)
			prs->env[i++] = env->vars[prs->j][prs->count++];
		prs->env[i] = '\0';
		_push_back_string_(prs->global, prs->g, prs->env, size);
		prs->g += size;
	}
}

void	_copy_dollar_digits_(t_mp *prs)
{
	char	*tmp;

	tmp = ft_strdup("bash");
	if (prs->buff[++prs->i] == 48)
	{
		_push_back_string_(prs->global, prs->g, tmp, 4);
		prs->g +=4;
		prs->i++;
	}
	else
		prs->i++;
}
