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
			while (s[i] != '"')
			{
				if (s[i] == '\\')
				{
					i += 2;
					continue;
				}
				i++;
			}
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


char				**_split_tokens(s_split *sp, char const *s, char c)
{
	int i;
	int start;
	int end;

	i = 0;
	if (!s)
		return (NULL);
	sp->size = _count_tokens(s, c, sp);
	printf("size = |%d|\n", sp->size);
	if (!(sp->p = (char **)malloc(sizeof(char*) * (sp->size + 1))))
		return (NULL);
	while (sp->i < sp->size)
	{
		while (s[i] && s[i] == c)
			i++;
		if (!(sp->p[sp->i] = (char *)malloc(sizeof(char) * (_len_tokens(sp, s, c) + 1))))
			return (_free(sp));
		sp->j = 0;
		while (s[i])
        {
			if (s[i] == '"')
			{
				start = i++;
				while (s[i] != '"')
				{
					if (s[i] == '\\')
					{
						i += 2;
						continue;
					}
					i++;
				}
				end = i++;
				printf("before->|%s|\n", sp->p[sp->i]);
				ft_strlcat(sp->p[sp->i], (s + start), end);
				printf("after->|%s|\n", sp->p[sp->i]);
				sp->j += end - start;
			}
            else
				sp->p[sp->i][sp->j++] = s[i++];
            if (s[i] == c)
                break;
        }
		sp->p[sp->i++][sp->j] = '\0';
	}
	sp->p[sp->i] = NULL;
	sp->i = 0;
	_trim_tokens(sp->p);
	return (sp->p);
}
