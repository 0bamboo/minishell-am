/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_vars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 11:48:20 by abdait-m          #+#    #+#             */
/*   Updated: 2021/04/30 16:24:36 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	_copy_command_status(t_mp *prs)
{
	char	*tmp;

	tmp = ft_itoa(prs->status);
	prs->count = ft_strlen(tmp);
	_push_back_string_(prs->global, prs->g, tmp, prs->count);
	prs->g += prs->count;
	prs->i += 2;
	free(tmp);
}

void	_copy_inside_dq_(t_mp *prs)
{
	prs->global[prs->g++] = prs->buff[prs->i++];
	while (prs->buff[prs->i] != '"' && prs->buff[prs->i])
	{
		if (prs->buff[prs->i] == '$' && ft_isdigit(prs->buff[prs->i + 1]))
			_copy_dollar_digits_(prs);
		else if (prs->buff[prs->i] == '\\')
		{
			prs->global[prs->g++] = prs->buff[prs->i++];
			prs->global[prs->g++] = prs->buff[prs->i++];
		}
		else if (prs->buff[prs->i] == '$' && _isspec_(prs->buff[prs->i + 1]))
			prs->i += 2;
		else if (prs->buff[prs->i] == '$' && ft_isalpha(prs->buff[prs->i + 1]))
			_copy_env_vars_(prs);
		else if (prs->buff[prs->i] == '$' && prs->buff[prs->i + 1] == '?')
			_copy_command_status(prs);
		else
			prs->global[prs->g++] = prs->buff[prs->i++];
	}
	prs->global[prs->g++] = prs->buff[prs->i++];
}

void	_copy_inside_sq_(t_mp *prs)
{
	prs->global[prs->g++] = prs->buff[prs->i++];
	while (prs->buff[prs->i] && prs->buff[prs->i] != '\'')
		prs->global[prs->g++] = prs->buff[prs->i++];
	prs->global[prs->g++] = prs->buff[prs->i++];
}

void	_get_env_vars_2_(t_mp *prs)
{
	if (prs->buff[prs->i] == '$' && prs->buff[prs->i + 1] == '?')
		_copy_command_status(prs);
	else if (prs->buff[prs->i] == '$' && _isspec_(prs->buff[prs->i + 1]))
		prs->i += 2;
	else if (prs->buff[prs->i] == '$' && ft_isdigit(prs->buff[prs->i + 1]))
		_copy_dollar_digits_(prs);
	else if (prs->buff[prs->i] == '$' && ft_isalpha(prs->buff[prs->i + 1]))
		_copy_env_vars_(prs);
	else if (prs->buff[prs->i] == '"')
		_copy_inside_dq_(prs);
	else if (prs->buff[prs->i] == '\'')
		_copy_inside_sq_(prs);
	else
		prs->global[prs->g++] = prs->buff[prs->i++];
}

char	*_get_env_vars_(char *buffer, t_mp *prs)
{
	int	counter;

	prs->g = 0;
	counter = 0;
	prs->status = 12345;
	prs->buff = buffer;
	counter = _line_counter_(prs);
	prs->global = (char *)malloc(sizeof(char *) * (counter + 1));
	prs->i = 0;
	while (prs->buff[prs->i])
		_get_env_vars_2_(prs);
	prs->global[prs->g] = '\0';
	// printf("after handling env : |%s|\n", prs->global);
	return (prs->global);
}
