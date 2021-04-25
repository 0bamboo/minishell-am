/* ************************************************************************** */
/*                                                                            */
/*                                                       :::       ::::::::   */
/*   ft_split_tokens.c                          		:+:       :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 15:40:07 by abdait-m          #+#    #+#             */
/*   Updated: 2021/03/20 13:53:04 by abdait-m         ###   ########.fr       */
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

void    _trim_tokens(t_sp *sp)
{
	int i;
	// char *tmp;

	i = -1;
	while (sp->str[++i])
		sp->str[i] = ft_strtrim(sp->str[i], " ");
}


void		_add_to_string_(t_sp *sp, int size)
{
	// int		i;

	while (sp->tmp[sp->start] && size-- > 0)
	{
		sp->str[sp->i][sp->j++] = sp->tmp[sp->start];
		sp->start++;
	}
}

void		_sp_handle_single_quotes_(t_sp *sp)
{
	sp->start = sp->idx++;
	// puts("h");
	while (sp->tmp[sp->idx] && sp->tmp[sp->idx] != '\'')
		sp->idx++;
	sp->end = ++sp->idx;
	_add_to_string_(sp, sp->end - sp->start);
	// return (sp->end - sp->start);
}

void		_sp_handle_double_quotes_(t_sp *sp)
{
	sp->start = sp->idx++;
	// puts("hdq");
	while (sp->tmp[sp->idx] && sp->tmp[sp->idx] != '"')
	{
		if (sp->tmp[sp->idx] == '\\')
		{
			sp->idx += 2;
			continue;
		}
		sp->idx++;
	}
	sp->end = ++sp->idx;
	_add_to_string_(sp, sp->end - sp->start);
	// puts("hdq out");
	// return (sp->end - sp->start);
}

void		_split_utils_(t_sp *sp, char delim)
{
	int size;

	while (sp->tmp[sp->idx] && sp->tmp[sp->idx] == delim)
		sp->idx++;
	size = _len_tokens(sp, delim);
	printf("len tokens === |%d|\n", size);
	// if (!(sp->str[sp->i] = (char *)malloc(sizeof(char) * (size + 1))))
	// 	return (_free(sp));
	sp->str[sp->i] = (char *)malloc(sizeof(char) * (size + 1));
	sp->j = 0;
}

void _split_utils_2_(t_sp *sp)
{
	// puts("im in2");
	if (sp->tmp[sp->idx] == '"')
		_sp_handle_double_quotes_(sp);
	else if (sp->tmp[sp->idx] == '\'')
		_sp_handle_single_quotes_(sp);
	else
		sp->str[sp->i][sp->j++] = sp->tmp[sp->idx++];
}

char				**_split_tokens(t_sp *sp, char *line, char delim)
{
	// test with this 
	//echo $bash12345"hi agina \\\$0 $abdennacer \\123451234512345?? hi \" \\\" out"
	//echo $$0$?"hi agina \\\$0 $$9abdennacer \\$?$?$??? hi \" \\\" out"
	sp->idx = 0;
	sp->tmp = line;
	if (!sp->tmp)
		return	NULL;
	sp->size = _count_tokens(delim, sp);
	printf("size of tokens = |%d|\n", sp->size);
	sp->str = (char **)malloc(sizeof(char*) * (sp->size + 1));
		// return (NULL);
	sp->i = 0;
	sp->k = 0;
	while (sp->i < sp->size)
	{
		_split_utils_(sp, delim);
		// puts("im in1");
		// while (sp->tmp[sp->idx] && sp->tmp[sp->idx] == delim)
		// 	sp->idx++;
		// // puts("im in2");
		// int size;
		// size = _len_tokens(sp, delim);
		// printf("len tokens === |%d|\n", size);
		// // if (!(sp->str[sp->i] = (char *)malloc(sizeof(char) * (size + 1))))
		// // 	return (_free(sp));
		// sp->str[sp->i] = (char *)malloc(sizeof(char) * (size + 1));
		// sp->j = 0;
		// puts("im in3");
		while (sp->tmp[sp->idx])
        {
			// puts("im in");
			_split_utils_2_(sp);
			// if (sp->tmp[sp->idx] == '"')
			// 	_sp_handle_double_quotes_(sp);
			// else if (sp->tmp[sp->idx] == '\'')
			// 	_sp_handle_single_quotes_(sp);
            // else
			// 	sp->str[sp->i][sp->j++] = sp->tmp[sp->idx++];
            if (sp->tmp[sp->idx] == delim)
			{
				sp->k = sp->idx + 1;
				printf("idx = |%c|\n", sp->tmp[sp->k]);
                break;
			}
			// printf("-%c-\n", sp->tmp[sp->idx]);
        }
		// puts("im out");
		sp->str[sp->i++][sp->j] = '\0';
	}
	sp->str[sp->i] = NULL;
	_trim_tokens(sp);
	free(line);
	return (sp->str);
}
