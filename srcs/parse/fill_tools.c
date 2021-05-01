/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 22:54:42 by abdait-m          #+#    #+#             */
/*   Updated: 2021/04/22 22:54:42 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	_count_token_length_in_dq_(t_mp *prs)
{
	prs->j++;
	while (prs->buff[prs->j] && prs->buff[prs->j] != '"')
	{
		if (prs->buff[prs->j] == '\\')
		{
			prs->j += 2;
			continue ;
		}
		prs->j++;
	}
}

void	_count_token_length_2_(t_mp *prs)
{
	prs->count++;
	while (prs->buff[prs->j] && prs->buff[prs->j] != ' '
		&& prs->buff[prs->j] != '>' && prs->buff[prs->j] != '<')
	{
		if (prs->buff[prs->j] == '"')
			_count_token_length_in_dq_(prs);
		else if (prs->buff[prs->j] == '\'')
			while (prs->buff[++prs->j] && prs->buff[prs->j] != '\'')
				;
		prs->j++;
	}
	prs->j--;
}

int	_count_token_length_(t_mp *prs)
{
	prs->j = -1;
	prs->count = 0;
	while (prs->buff[++prs->j])
	{
		if (prs->buff[prs->j] == ' ')
			continue ;
		else if (prs->buff[prs->j] == '>' || prs->buff[prs->j] == '<')
		{
			prs->count++;
			if (prs->buff[prs->j + 1] == '>')
				prs->j++;
		}
		else
			_count_token_length_2_(prs);
	}
	return (prs->count);
}

void	_size_of_arg_dq_(t_mp *prs)
{
	prs->j++;
	prs->counter++;
	while (prs->temp[prs->j] && prs->temp[prs->j] != '"')
	{
		if (prs->temp[prs->j] == '\\')
		{
			prs->counter += 2;
			prs->j += 2;
			continue ;
		}
		prs->j++;
		prs->counter++;
	}
}

void	_size_of_arg_sq_(t_mp *prs)
{
	prs->counter++;
	prs->j++;
	while (prs->temp[prs->j] && prs->temp[prs->j] != '\'')
	{
		prs->counter++;
		prs->j++;
	}
}

int	_size_of_arg_(t_mp *prs, char *buffer, int i)
{
	prs->counter = 0;
	prs->j = i;
	prs->temp = buffer;
	while (prs->temp[prs->j] && prs->temp[prs->j] == ' ')
		prs->j++;
	while (prs->temp[prs->j])
	{
		if (prs->temp[prs->j] == '"')
			_size_of_arg_dq_(prs);
		else if (prs->temp[prs->j] == '\'')
			_size_of_arg_sq_(prs);
		if (prs->temp[prs->j] == ' ' || prs->temp[prs->j] == '>'
			|| prs->temp[prs->j] == '<')
			break ;
		prs->j++;
		prs->counter++;
	}
	return (prs->counter);
}
