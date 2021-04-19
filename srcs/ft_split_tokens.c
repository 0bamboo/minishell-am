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


static int			_count_tokens(char c, t_sp *sp)
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

static int			_len_tokens(t_sp *sp, char c)
{
	sp->count = 0;
	while (sp->tmp[sp->k] && sp->tmp[sp->k] != c)
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

// static char			**_free(t_sp *sp)
// {
// 	int i;

// 	i = 0;
// 	puts("here");
// 	while (i++ < sp->size)
// 		free(prs->cmds[i]);
// 	puts("here1");
// 	free(prs->cmds);
// 	prs->cmds = NULL;
// 	return (NULL);
// }

void    _trim_tokens(t_mp *prs)
{
	int i;
	// char *tmp;

	i = -1;
	while (prs->cmds[++i])
		prs->cmds[i] = ft_strtrim(prs->cmds[i], " ");
}


void		_add_to_string_(t_sp *sp, int size, t_mp *prs)
{
	// int		i;

	// i = ft_strlen(prs->cmds[sp->i]);
	while (sp->tmp[sp->start] && size-- > 0)
	{
		prs->cmds[sp->i][sp->j++] = sp->tmp[sp->start];
		sp->start++;
	}
}

void		_sp_handle_single_quotes_(t_sp *sp, t_mp *prs)
{
	sp->start = sp->idx++;
	// puts("h");
	while (sp->tmp[sp->idx] && sp->tmp[sp->idx] != '\'')
		sp->idx++;
	sp->end = ++sp->idx;
	_add_to_string_(sp, sp->end - sp->start, prs);
	// return (sp->end - sp->start);
}

void		_sp_handle_double_quotes_(t_sp *sp, t_mp *prs)
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
	_add_to_string_(sp, sp->end - sp->start, prs);
	// puts("hdq out");
	// return (sp->end - sp->start);
}

void				_split_tokens(t_mp *prs, t_sp *sp, char *line, char c)
{
	// test with this 
	//echo $bash12345"hi agina \\\$0 $abdennacer \\123451234512345?? hi \" \\\" out"
	//echo $$0$?"hi agina \\\$0 $$9abdennacer \\$?$?$??? hi \" \\\" out"
	sp->idx = 0;
	sp->tmp = line;
	if (!sp->tmp)
		return;
	sp->size = _count_tokens(c, sp);
	printf("size of tokens = |%d|\n", sp->size);
	prs->cmds = (char **)malloc(sizeof(char*) * (sp->size + 1));
		// return (NULL);
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
		// if (!(prs->cmds[sp->i] = (char *)malloc(sizeof(char) * (size + 1))))
		// 	return (_free(sp));
		prs->cmds[sp->i] = (char *)malloc(sizeof(char) * (size + 1));
		sp->j = 0;
		// puts("im in3");
		while (sp->tmp[sp->idx])
        {
			// puts("im in");
			if (sp->tmp[sp->idx] == '"')
				_sp_handle_double_quotes_(sp, prs);
			else if (sp->tmp[sp->idx] == '\'')
				_sp_handle_single_quotes_(sp, prs);
            else
				prs->cmds[sp->i][sp->j++] = sp->tmp[sp->idx++];
            if (sp->tmp[sp->idx] == c)
			{
				sp->k = sp->idx + 1;
				printf("idx = |%c|\n", sp->tmp[sp->k]);
                break;
			}
			// printf("-%c-\n", sp->tmp[sp->idx]);
        }
		// puts("im out");
		prs->cmds[sp->i++][sp->j] = '\0';
	}
	prs->cmds[sp->i] = NULL;
	_trim_tokens(prs);
	// free(line);
	// return (prs->cmds);
}
