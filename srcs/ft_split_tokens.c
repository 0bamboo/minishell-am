/* ************************************************************************** */
/*                                                                            */
/*                                                      :::      ::::::::   */
/*   ft_split_tokens_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 15:40:07 by abdait-m          #+#    #+#             */
/*   Updated: 2021/03/20 13:53:04 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// static int			_count_tokens(char const *s, char c)
// {
// 	int	count;

// 	count = 0;
// 	while (*s && *s == c)
// 		s++;
// 	while (*s)
// 	{
// 		if ((*s == c && *(s + 1) != c) || *(s + 1) == '\0')
// 			count++;
// 		s++;
// 	}
// 	return (count);
// }

// static int			_len_tokens(char const *s, char c)
// {
// 	int	k;

// 	k = 0;
// 	while (s[k] && s[k] != c)
// 		k++;
// 	return (k);
// }

// static char			**_free(char **ptr, int size)
// {
// 	int i;

// 	i = 0;
// 	while (i++ < size)
// 		free(ptr[i]);
// 	free(ptr);
// 	ptr = NULL;
// 	return (NULL);
// }

// char		**ft_split_tokens(char const *s, char c)
// {
// 	char		**p;
// 	int			size;
// 	int			i;
// 	int			j;

// 	if (!s)
// 		return (NULL);
// 	size = _count_tokens(s, c);
// 	if (!(p = (char **)malloc(sizeof(char*) * (size + 1))))
// 		return (NULL);
// 	i = 0;
// 	while (i < size)
// 	{
// 		while (*s && *s == c)
// 			s++;
// 		if (!(p[i] = (char *)malloc(sizeof(char) * (_len_tokens(s, c) + 1))))
// 			return (_free(p, size));
// 		j = 0;
// 		while (*s && *s != c)
// 			p[i][j++] = *s++;
// 		p[i++][j] = '\0';
// 	}
// 	p[i] = NULL;
// 	return (p);
// }

// typedef struct 
// {
//     char **p;
//     int size;
//     int i;
//     int j;
//     int check_dq;
//     int check_sq;
// } s_split;

static int			_count_tokens(char const *s, char c, s_split *sp)
{
	int	count;

	count = 0;
	while (*s && *s == c)
		s++;
	while (*s)
	{
        if ('"' == *s && sp->check_sq % 2 == 0)
            sp->check_dq += 1;
        if ('\'' == *s && sp->check_dq % 2 == 0)
            sp->check_sq += 1;
		if ((((*s == c && *(s + 1) != c) || *(s + 1) == '\0')) && sp->check_sq % 2 == 0 && sp->check_dq % 2 == 0)
			count++;
		s++;
	}
	sp->check_sq = 0;
	sp->check_dq = 0;
    // printf("how many words : %d\n", count);
	return (count);
}

static int			_len_tokens(s_split *sp, char const *s, char c)
{
	int	k;

	k = 0;
	while (s[k])
	{
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
	// char **tab;
	// int size;
	
	if (!s)
		return (NULL);
	sp->size = _count_tokens(s, c, sp);
	if (!(sp->p = (char **)malloc(sizeof(char*) * (sp->size + 1))))
		return (NULL);
	while (sp->i < sp->size)
	{
		while (*s && *s == c)
			s++;
		// So the problem is in _len_tokens : when you calculate each string length you stop when you find the the fist delimeter
		// fixed maybe....
		if (!(sp->p[sp->i] = (char *)malloc(sizeof(char) * (_len_tokens(sp, s, c) + 1))))
			return (_free(sp));
		sp->j = 0;
		while (*s)
        {
            if (*s == '\'' && sp->check_dq % 2 == 0)
                sp->check_sq += 1;
            if (*s == '"' && sp->check_sq % 2 == 0)
                sp->check_dq += 1;
            sp->p[sp->i][sp->j++] = *s++;
            if (*s == c && sp->check_dq % 2 == 0 && sp->check_sq % 2 == 0)
                break;
        }
		sp->p[sp->i++][sp->j] = '\0';
	}
	sp->p[sp->i] = NULL;
	sp->i = 0;
	// printf("split --> |%d|\n", sp->i);
	_trim_tokens(sp->p);
	return (sp->p);
}
