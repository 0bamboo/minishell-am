/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_vars_tools.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 14:01:12 by abdait-m          #+#    #+#             */
/*   Updated: 2021/05/07 00:33:25 by abdait-m         ###   ########.fr       */
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
	while (*fill && size > 0)
	{
		buff[index++] = *fill++;
		size--;
	}
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

void _env_var_copy_(t_mp *prs, t_envlist *env)
{
	int	size;
	int	i;
	int found;

	prs->j = -1;
	found = 0;
	while (env->vars[++prs->j])
	{
		if (!ft_strncmp(prs->temp, env->vars[prs->j], prs->count))
		{
			size = ft_strlen(env->vars[prs->j]) - prs->count;
			prs->env = malloc(sizeof(char) * (size + 1));
			if (!prs->env)
				return ;
			found = 1;
			break ;
		}
	}
	i = 0;
	if (found)
	{
		while (env->vars[prs->j][prs->count] && i < size)
			prs->env[i++] = env->vars[prs->j][prs->count++];
		prs->env[i] = '\0';
		_push_back_string_(prs->global, prs->g, prs->env, size);
		prs->g += size;
	}
}

void	_count_env_vars_(t_mp *prs, t_envlist *env)
{
	prs->count = 0;
	prs->j = ++prs->i;
	while ((ft_isalpha(prs->buff[prs->j]) || ft_isdigit(prs->buff[prs->i]))
		&& prs->buff[prs->j++])
		prs->count++;
	prs->count++;
	prs->temp = (char *)malloc(sizeof(char) * (prs->count + 1));
	if (!prs->temp)
		return ;
	prs->j = 0;
	while ((ft_isalpha(prs->buff[prs->i]) || ft_isdigit(prs->buff[prs->i]))
		&& prs->buff[prs->i])
		prs->temp[prs->j++] = prs->buff[prs->i++];
	prs->temp[prs->j++] = '=';
	prs->temp[prs->j] = '\0';
	_env_var_counter_(prs, env);
	free(prs->temp);
	prs->temp = NULL;
}

void	_copy_dollar_digits_(t_mp *prs)
{
	if (prs->buff[++prs->i] == 48)
	{
		_push_back_string_(prs->global, prs->g, "bash", 4);
		prs->g +=4;
		prs->i++;
	}
	else
		prs->i++;
}

void	_copy_env_vars_(t_mp *prs, t_envlist *env)
{
	prs->count = 0;
	prs->j = ++prs->i;
	while ((ft_isalpha(prs->buff[prs->j]) || ft_isdigit(prs->buff[prs->i]))
		&& prs->buff[prs->j++])
		prs->count++;
	prs->count++;
	prs->temp = (char *)malloc(sizeof(char) * (prs->count + 1));
	if (!prs->temp)
		return ;
	prs->j = 0;
	while ((ft_isalpha(prs->buff[prs->i]) || ft_isdigit(prs->buff[prs->i]))
		&& prs->buff[prs->i])
		prs->temp[prs->j++] = prs->buff[prs->i++];
	prs->temp[prs->j++] = '=';
	prs->temp[prs->j] = '\0';
	_env_var_copy_(prs, env);
	free(prs->temp);
	prs->temp = NULL;
}
