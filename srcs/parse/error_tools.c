/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 14:25:42 by abdait-m          #+#    #+#             */
/*   Updated: 2021/05/01 14:30:15 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	_char_in_tab_(char c, char arr[3])
{
	if (c == arr[0] || c == arr[1] || c == arr[2])
		return (1);
	return (0);
}

int	_is_white_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\r' || c == '\n')
		return (1);
	return (0);
}

int	_check_semi_colon(char *line, t_mp *prs)
{
	prs->i++;
	if (line[0] == ';')
	{
		prs->er = 1;
		return (prs->i);
	}
	while (prs->i)
	{
		if (line[prs->i] == '|' || line[prs->i] == ';')
		{
			prs->er = 1;
			break ;
		}
		else if (_is_white_space(line[prs->i]))
			prs->i++;
		else
			break ;
	}
	return (--prs->i);
}

int	_check_pipe(char *line, t_mp *prs)
{
	prs->i++;
	if (line[0] == '|' || !line[prs->i + 1])
	{
		prs->er = 1;
		return (prs->i);
	}
	while (line[prs->i])
	{
		if (_is_white_space(line[prs->i]))
			prs->i++;
		else if (line[prs->i] == '|' || line[prs->i] == ';'
			|| line[prs->i] == '>' || line[prs->i] == '<')
		{
			prs->er = 1;
			break ;
		}
		else
			break ;
	}
	return (--prs->i);
}

int	_check_single_quotes(char *line, t_mp *prs)
{
	prs->i++;
	while (line[prs->i] != '\'' && line[prs->i])
		prs->i++;
	if (line[prs->i] != prs->tmp)
		prs->er = 1;
	return (prs->i);
}
