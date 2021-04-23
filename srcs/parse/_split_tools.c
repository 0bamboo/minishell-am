/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _split_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 00:47:04 by abdait-m          #+#    #+#             */
/*   Updated: 2021/04/23 00:47:04 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void _count_tokens_dq_(t_sp *sp)
{
	sp->i++;
	while (sp->tmp[sp->i] && sp->tmp[sp->i] != '"')
	{
		if (sp->tmp[sp->i] == '\\')
		{
			sp->i += 2;
			continue;
		}
		sp->i++;
	}
}

int			_count_tokens(char delim, t_sp *sp)
{
	sp->count = 0;
	sp->i = 0;
	while (sp->tmp[sp->i] && sp->tmp[sp->i] == delim)
		sp->i++;
	while (sp->tmp[sp->i])
	{
		if (sp->tmp[sp->i] == '"')
		{
			_count_tokens_dq_(sp);
			// sp->i++;
			// while (sp->tmp[sp->i] && sp->tmp[sp->i] != '"')
			// {
			// 	if (sp->tmp[sp->i] == '\\')
			// 	{
			// 		sp->i += 2;
			// 		continue;
			// 	}
			// 	sp->i++;
			// }
		}
		else if (sp->tmp[sp->i] == '\'')
		{
			// sp->i++;
			while (sp->tmp[++sp->i] && sp->tmp[sp->i] != '\'');
				// sp->i++;
		}
		if ((((sp->tmp[sp->i] == delim && sp->tmp[sp->i + 1] != delim) || sp->tmp[sp->i + 1] == '\0')))
			sp->count++;
		sp->i++;
	}
	return (sp->count);
}

void _len_tokens_dq_(t_sp *sp)
{
	sp->k++;
	sp->count++;
	while (sp->tmp[sp->k] && sp->tmp[sp->k] != '"')
	{
		if (sp->tmp[sp->k] == '\\')
		{
			sp->k += 2;
			sp->count += 2;
			continue;
		}
		sp->k++;
		sp->count++;
	}
}

void _len_tokens_sq_(t_sp *sp)
{
	sp->k++;
	sp->count++;
	while (sp->tmp[sp->k] && sp->tmp[sp->k] != '\'')
	{
		sp->count++;
		sp->k++;
	}	
}

int			_len_tokens(t_sp *sp, char delim)
{
	sp->count = 0;
	while (sp->tmp[sp->k] && sp->tmp[sp->k] != delim)
	{
		if (sp->tmp[sp->k] == '"')
			_len_tokens_dq_(sp);
		else if (sp->tmp[sp->k] == '\'')
			_len_tokens_sq_(sp);
		sp->k++;
		sp->count++;
	}
	return (sp->count);
}