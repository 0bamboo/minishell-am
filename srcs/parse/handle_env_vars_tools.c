/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_vars_tools.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 14:01:12 by abdait-m          #+#    #+#             */
/*   Updated: 2021/05/05 15:04:22 by abdait-m         ###   ########.fr       */
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

void	_count_env_vars_(t_mp *prs, t_envlist *env)
{
	prs->count = 0;
	prs->j = ++prs->i;
	while ((ft_isalpha(prs->buff[prs->j]) || ft_isdigit(prs->buff[prs->i]))
		&& prs->buff[prs->j++])
		prs->count++;
	prs->temp = (char *)malloc(sizeof(char) * (prs->count + 1));
	prs->j = 0;
	while ((ft_isalpha(prs->buff[prs->i]) || ft_isdigit(prs->buff[prs->i]))
		&& prs->buff[prs->i])
		prs->temp[prs->j++] = prs->buff[prs->i++];
	prs->temp[prs->j++] = '=';
	prs->temp[prs->j] = '\0';
	printf("prs->temp = |%s|\n", prs->temp);
	// prs->env = getenv(prs->temp);
	int i = -1;
	puts("env =========== ");
	while (env->vars[++i])
	{
		if (!ft_strncmp(prs->temp, env->vars[i], prs->count + 1))
		{
			ft_strcpy(prs->env, env->vars[i] + prs->count + 1);
			printf("length = |%lu|", ft_strlen(prs->env));
		}
		printf("env = |%s|\n", env->vars[i]);
	}
	puts("env =========== ");
	if (prs->env)
		prs->counter += ft_strlen(prs->env);
	free(prs->temp);
	// free(prs->env);
	prs->temp = NULL;
	prs->env = NULL;
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
	prs->temp = (char *)malloc(sizeof(char) * (prs->count + 1));
	prs->j = 0;
	while ((ft_isalpha(prs->buff[prs->i]) || ft_isdigit(prs->buff[prs->i]))
		&& prs->buff[prs->i])
		prs->temp[prs->j++] = prs->buff[prs->i++];
	prs->temp[prs->j++] = '=';
	prs->temp[prs->j] = '\0';
	// prs->env = getenv(prs->temp);
	int i = -1;
	while (env->vars[++i])
	{
		if (!ft_strncmp(prs->temp, env->vars[i], prs->count + 1))
		{
			ft_strcpy(prs->env, env->vars[prs->count + 1]);
			printf("FOUND = |%s|\n", prs->env);
		}
	}
	if (prs->env)
	{
		prs->count = ft_strlen(prs->env);
		_push_back_string_(prs->global, prs->g, prs->env, prs->count);
		prs->g += prs->count;
	}
	// free(prs->env);
	free(prs->temp);
	prs->env = NULL;
	prs->temp = NULL;
}
