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


static int			_count_tokens(char const *s, char c, s_split *sp)
{
	int	count;
	int i;

	count = 0;
	i = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == '"')
		{
			i++;
			while (s[i] && s[i] != '"')
			{
				if (s[i] == '\\')
				{
					i += 2;
					continue;
				}
				i++;
			}
		}
		else if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
				i++;
		}
		if ((((s[i] == c && s[i + 1] != c) || s[i + 1] == '\0')))
			count++;
		i++;
	}
	sp->check_sq = 0;
	sp->check_dq = 0;
	return (count);
}

static int			_len_tokens(s_split *sp, char const *s, char c)
{
	int	k;

	k = 0;
	// try to change this method that you used here ok
	while (s[k])
	{
		if (s[k] == '\\' && s[k + 1] == '"')
		{
			k += 2;
			continue;
		}
		if (s[k] == '\'' && sp->check_dq % 2 == 0)
			sp->check_sq += 1;
		if (s[k] == '"' && sp->check_sq % 2 == 0)
			sp->check_dq += 1;
		if (s[k] == c && sp->check_dq % 2 == 0 && sp->check_sq % 2 == 0)
			break;
		k++;
	}
	sp->check_sq = 0;
	sp->check_dq = 0;
	return (k);
}

static char			**_free(s_split *sp)
{
	int i;

	i = 0;
	while (i++ < sp->size)
		free(sp->p[i]);
	free(sp->p);
	sp->p = NULL;
	return (NULL);
}

void _trim_tokens(char **tab)
{
	int i;

	i = -1;
	while (tab[++i])
		tab[i] = ft_strtrim(tab[i], " ");
}


void		_add_to_string_(char *dest, const char *src, int size)
{
	int		i;

	i = ft_strlen(dest);
	while (*src && size > 0)
	{
		dest[i++] = *src++;
		size--;
	}
}

int		_sp_handle_single_quotes_(s_split *sp, char const *s)
{
	int start;
	int end;

	start = sp->idx++;
	while (s[sp->idx] && s[sp->idx] != '\'')
		sp->idx++;
	end = ++sp->idx;
	_add_to_string_(sp->p[sp->i], (start + s), end - start);
	return (end - start);
}

int		_sp_handle_double_quotes_(s_split *sp, char const *s)
{
	int start;
	int end;

	start = sp->idx++;
	while (s[sp->idx] && s[sp->idx] != '"')
	{
		if (s[sp->idx] == '\\')
		{
			sp->idx += 2;
			continue;
		}
		sp->idx++;
	}
	end = ++sp->idx;
	_add_to_string_(sp->p[sp->i], (s + start), end - start);
	return (end - start);
}

char				**_split_tokens(s_split *sp, char const *s, char c)
{
	sp->idx = 0;
	if (!s)
		return (NULL);
	sp->size = _count_tokens(s, c, sp);
	printf("size of tokens = |%d|\n", sp->size);
	if (!(sp->p = (char **)malloc(sizeof(char*) * (sp->size + 1))))
		return (NULL);
	sp->i = 0;
	sp->k = 0;
	while (sp->i < sp->size)
	{
		// puts("im in1");
		while (s[sp->idx] && s[sp->idx] == c)
			sp->idx++;
		// puts("im in2");
		int size;
		size = _len_tokens(sp, s + sp->k, c);
		printf("size === |%d|\n", size);
		if (!(sp->p[sp->i] = (char *)malloc(sizeof(char) * (size + 1))))
			return (_free(sp));
		sp->j = 0;
		// puts("im in3");
		while (s[sp->idx])
        {
			if (s[sp->idx] == '"')
				sp->j += _sp_handle_double_quotes_(sp, s);
			else if (s[sp->idx] == '\'')
				sp->j += _sp_handle_single_quotes_(sp, s);
            else
				sp->p[sp->i][sp->j++] = s[sp->idx++];
            if (s[sp->idx] == c)
			{
				sp->k = sp->idx + 1;
				printf("idx = |%c|\n", s[sp->k]);
                break;
			}
			// printf("-%c-\n", s[sp->idx]);
        }
		// puts("im out");
		sp->p[sp->i++][sp->j] = '\0';
	}
	sp->p[sp->i] = NULL;
	_trim_tokens(sp->p);
	return (sp->p);
}
