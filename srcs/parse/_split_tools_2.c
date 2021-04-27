/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _split_tools_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 14:01:16 by abdait-m          #+#    #+#             */
/*   Updated: 2021/04/27 00:58:35 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static char			**_free(t_sp *sp)
// {
// 	int i;

// 	i = 0;
// 	puts("here");
// 	while (i++ < sp->size)
// 		free(sp->str[i]);
// 	puts("here1");
// 	free(sp->str);
// 	sp->str = NULL;
// 	return (NULL);
// }

void	_trim_tokens(t_sp *sp)
{
	int	i;
	char *tmp;

	i = -1;
	while (sp->str[++i])
	{
		tmp = ft_strtrim(sp->str[i], " ");
		free(sp->str[i]);
		sp->str[i] = tmp;
		
	}
}

void	_add_to_string_(t_sp *sp, int size)
{
	while (sp->tmp[sp->start] && size-- > 0)
	{
		sp->str[sp->i][sp->j++] = sp->tmp[sp->start];
		sp->start++;
	}
}

void	_sp_handle_single_quotes_(t_sp *sp)
{
	sp->start = sp->idx++;
	while (sp->tmp[sp->idx] && sp->tmp[sp->idx] != '\'')
		sp->idx++;
	sp->end = ++sp->idx;
	_add_to_string_(sp, sp->end - sp->start);
}