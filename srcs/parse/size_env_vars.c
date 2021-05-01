/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_env_vars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 14:01:04 by abdait-m          #+#    #+#             */
/*   Updated: 2021/04/30 16:33:38 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	_count_dollar_digits_(t_mp *prs)
{
	if (prs->buff[++prs->i] == '0')
	{
		prs->i++;
		prs->counter += 4;
	}
	else
		prs->i++;
}

void	_count_command_status(t_mp *prs)
{
	char	*tmp;

	prs->i += 2;
	tmp = ft_itoa(prs->status);
	prs->counter += ft_strlen(tmp);
	free(tmp);
}

void	_count_inside_dq_(t_mp *prs)
{
	prs->counter++;
	prs->i++;
	while (prs->buff[prs->i] != '"' && prs->buff[prs->i])
	{
		if (prs->buff[prs->i] == '$' && ft_isdigit(prs->buff[prs->i + 1]))
			_count_dollar_digits_(prs);
		else if (prs->buff[prs->i] == '\\')
		{
			prs->i += 2;
			prs->counter += 2;
		}
		else if (prs->buff[prs->i] == '$' && ft_isalpha(prs->buff[prs->i + 1]))
			_count_env_vars_(prs);
		else if (prs->buff[prs->i] == '$' && prs->buff[prs->i + 1] == '?')
			_count_command_status(prs);
		else
		{
			prs->counter++;
			prs->i++;
		}
	}
	prs->counter++;
	prs->i++;
}

void	_count_inside_sq_(t_mp *prs)
{
	prs->i++;
	prs->counter++;
	while (prs->buff[prs->i] && prs->buff[prs->i] != '\'')
	{
		prs->i++;
		prs->counter++;
	}
	prs->i++;
	prs->counter++;
}

int	_line_counter_(t_mp *prs)
{
	prs->i = 0;
	prs->counter = 0;
	while (prs->buff[prs->i])
	{
		if (prs->buff[prs->i] == '$' && prs->buff[prs->i + 1] == '?')
			_count_command_status(prs);
		else if (prs->buff[prs->i] == '$' && _isspec_(prs->buff[prs->i + 1]))
			prs->i += 2;
		else if (prs->buff[prs->i] == '$' && ft_isdigit(prs->buff[prs->i + 1]))
			_count_dollar_digits_(prs);
		else if (prs->buff[prs->i] == '$' && ft_isalpha(prs->buff[prs->i + 1]))
			_count_env_vars_(prs);
		else if (prs->buff[prs->i] == '"')
			_count_inside_dq_(prs);
		else if (prs->buff[prs->i] == '\'')
			_count_inside_sq_(prs);
		else if (prs->buff[prs->i])
		{
			prs->counter++;
			prs->i++;
		}
	}
	return (prs->counter);
}
