/* ************************************************************************** */
/*                                                                            */
/*                                                       :::       ::::::::   */
/*   ft_split_tokens.c                          		:+:       :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 15:40:07 by abdait-m          #+#    #+#             */
/*   Updated: 2021/04/28 15:14:12 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	_sp_handle_double_quotes_(t_sp *sp)
{
	sp->start = sp->idx++;
	while (sp->tmp[sp->idx] && sp->tmp[sp->idx] != '"')
	{
		if (sp->tmp[sp->idx] == '\\')
		{
			sp->idx += 2;
			continue ;
		}
		sp->idx++;
	}
	sp->end = ++sp->idx;
	_add_to_string_(sp, sp->end - sp->start);
}

void	_split_utils_(t_sp *sp, char delim)
{
	int	size;

	while (sp->tmp[sp->idx] && sp->tmp[sp->idx] == delim)
		sp->idx++;
	size = _len_tokens(sp, delim);
	sp->str[sp->i] = (char *) malloc(sizeof(char) * (size + 1));
	if (!sp->str[sp->i])
		return ;
	sp->j = 0;
}

void	_split_utils_2_(t_sp *sp)
{
	if (sp->tmp[sp->idx] == '"')
		_sp_handle_double_quotes_(sp);
	else if (sp->tmp[sp->idx] == '\'')
		_sp_handle_single_quotes_(sp);
	else
		sp->str[sp->i][sp->j++] = sp->tmp[sp->idx++];
}

void	_split_(t_sp *sp, char delim)
{
	_split_utils_(sp, delim);
	while (sp->tmp[sp->idx])
	{
		_split_utils_2_(sp);
		if (sp->tmp[sp->idx] == delim)
		{
			sp->k = sp->idx + 1;
			break ;
		}
	}
}

char	**_split_tokens(t_sp *sp, char *line, char delim)
{
	sp->tmp = line;
	if (!sp->tmp)
		return (NULL);
	sp->size = _count_tokens(delim, sp);
	sp->str = (char **) malloc(sizeof(char *) * (sp->size + 1));
	if (!sp->str)
		return (NULL);
	sp->i = 0;
	sp->k = 0;
	sp->idx = 0;
	while (sp->i < sp->size)
	{
		_split_(sp, delim);
		sp->str[sp->i++][sp->j] = '\0';
	}
	sp->str[sp->i] = NULL;
	_trim_tokens(sp);
	return (sp->str);
}
