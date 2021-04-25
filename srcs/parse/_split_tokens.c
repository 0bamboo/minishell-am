/* ************************************************************************** */
/*                                                                            */
/*                                                       :::       ::::::::   */
/*   ft_split_tokens.c                          		:+:       :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 15:40:07 by abdait-m          #+#    #+#             */
/*   Updated: 2021/04/25 13:29:33 by abdait-m         ###   ########.fr       */
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

	i = -1;
	while (sp->str[++i])
		sp->str[i] = ft_strtrim(sp->str[i], " ");
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
	printf("len tokens === |%d|\n", size);
	sp->str[sp->i] = (char *)malloc(sizeof(char) * (size + 1));
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

char	**_split_tokens(t_sp *sp, char *line, char delim)
{
	sp->idx = 0;
	sp->tmp = line;
	if (!sp->tmp)
		return (NULL);
	sp->size = _count_tokens(delim, sp);
	printf("size of tokens = |%d|\n", sp->size);
	sp->str = (char **)malloc(sizeof(char*) * (sp->size + 1));
	sp->i = 0;
	sp->k = 0;
	while (sp->i < sp->size)
	{
		_split_utils_(sp, delim);
		while (sp->tmp[sp->idx])
		{
			_split_utils_2_(sp);
			if (sp->tmp[sp->idx] == delim)
			{
				sp->k = sp->idx + 1;
				printf("idx = |%c|\n", sp->tmp[sp->k]);
				break ;
			}
		}
		sp->str[sp->i++][sp->j] = '\0';
	}
	sp->str[sp->i] = NULL;
	_trim_tokens(sp);
	return (sp->str);
}
