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

#include "../includes/minishell.h"


static int			_count_tokens(char c, s_split *sp)
{
	sp->count = 0;
	sp->i = 0;
	while (sp->tmp[sp->i] && sp->tmp[sp->i] == c)
		sp->i++;
	while (sp->tmp[sp->i])
	{
		if (sp->tmp[sp->i] == '"')
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
		else if (sp->tmp[sp->i] == '\'')
		{
			sp->i++;
			while (sp->tmp[sp->i] && sp->tmp[sp->i] != '\'')
				sp->i++;
		}
		if ((((sp->tmp[sp->i] == c && sp->tmp[sp->i + 1] != c) || sp->tmp[sp->i + 1] == '\0')))
			sp->count++;
		sp->i++;
	}
	return (sp->count);
}

static int			_len_tokens(s_split *sp, char c)
{
	// sp->k = 0;
	// try to change this method that you used here ok
	sp->count = 0;
	while (sp->tmp[sp->k] && sp->tmp[sp->k] != c)
	{
		if (sp->tmp[sp->k] == '"')
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
		else if (sp->tmp[sp->k] == '\'')
		{
			sp->k++;
			sp->count++;
			while (sp->tmp[sp->k] && sp->tmp[sp->k] != '\'')
			{
				sp->count++;
				sp->k++;
			}	
		}
		sp->k++;
		sp->count++;
		// if (sp->tmp[k] == '\\' && s[k + 1] == '"')
		// {
		// 	k += 2;
		// 	continue;
		// }
		// if (s[k] == '\'' && sp->check_dq % 2 == 0)
		// 	sp->check_sq += 1;
		// if (s[k] == '"' && sp->check_sq % 2 == 0)
		// if (s[k] == c && sp->check_dq % 2 == 0 && sp->check_sq % 2 == 0)
		// 	break;
		// k++;
	}
	return (sp->count);
}

static char			**_free(s_split *sp)
{
	int i;

	i = 0;
	puts("here");
	while (i++ < sp->size)
		free(sp->str[i]);
	puts("here1");
	free(sp->str);
	sp->str = NULL;
	return (NULL);
}

void _trim_tokens(s_split *sp)
{
	int i;
	// char *tmp;

	i = -1;
	while (sp->str[++i])	
		sp->str[i] = ft_strtrim(sp->str[i], " ");
}


void		_add_to_string_(s_split *sp, int size)
{
	// int		i;

	// i = ft_strlen(sp->str[sp->i]);
	while (sp->tmp[sp->start] && size-- > 0)
	{
		sp->str[sp->i][sp->j++] = sp->tmp[sp->start];
		sp->start++;
	}
}

void		_sp_handle_single_quotes_(s_split *sp)
{
	sp->start = sp->idx++;
	// puts("h");
	while (sp->tmp[sp->idx] && sp->tmp[sp->idx] != '\'')
		sp->idx++;
	sp->end = ++sp->idx;
	_add_to_string_(sp, sp->end - sp->start);
	// return (sp->end - sp->start);
}

void		_sp_handle_double_quotes_(s_split *sp)
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

char				**_split_tokens(s_split *sp, char const *s, char c)
{
	// test with this echo $$0$?"hi agina \\\$0 $$9abdennacer \\$?$?$??? hi \" \\\" out"
	sp->idx = 0;
	sp->tmp = s;
	if (!sp->tmp)
		return (NULL);
	sp->size = _count_tokens(c, sp);
	printf("size of tokens = |%d|\n", sp->size);
	if (!(sp->str = (char **)malloc(sizeof(char*) * (sp->size + 1))))
		return (NULL);
	sp->i = 0;
	sp->k = 0;
	while (sp->i < sp->size)
	{
		// puts("im in1");
		while (sp->tmp[sp->idx] && sp->tmp[sp->idx] == c)
			sp->idx++;
		// puts("im in2");
		int size;
		size = _len_tokens(sp, c);
		printf("len tokens === |%d|\n", size);
		if (!(sp->str[sp->i] = (char *)malloc(sizeof(char) * (size + 1))))
			return (_free(sp));
		sp->j = 0;
		// puts("im in3");
		while (sp->tmp[sp->idx])
        {
			// puts("im in");
			if (sp->tmp[sp->idx] == '"')
				_sp_handle_double_quotes_(sp);
			else if (sp->tmp[sp->idx] == '\'')
				_sp_handle_single_quotes_(sp);
            else
				sp->str[sp->i][sp->j++] = sp->tmp[sp->idx++];
            if (sp->tmp[sp->idx] == c)
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
	return (sp->str);
}
