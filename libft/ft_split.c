/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 15:40:07 by abdait-m          #+#    #+#             */
/*   Updated: 2019/11/03 15:19:11 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_count_words(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s && *s == c)
		s++;
	while (*s)
	{
		if ((*s == c && *(s + 1) != c) || *(s + 1) == '\0')
			count++;
		s++;
	}
	return (count);
}

static int			ft_len_words(char const *s, char c)
{
	int	k;

	k = 0;
	while (s[k] && s[k] != c)
		k++;
	return (k);
}

static char			**ft_free(char **ptr, int size)
{
	int i;

	i = 0;
	while (i++ < size)
		free(ptr[i]);
	free(ptr);
	ptr = NULL;
	return (NULL);
}

char				**ft_split(char const *s, char c)
{
	char		**p;
	int			size;
	int			i;
	int			j;

	if (!s)
		return (NULL);
	size = ft_count_words(s, c);
	if (!(p = (char **)malloc(sizeof(char*) * (size + 1))))
		return (NULL);
	i = 0;
	while (i < size)
	{
		while (*s && *s == c)
			s++;
		if (!(p[i] = (char *)malloc(sizeof(char) * (ft_len_words(s, c) + 1))))
			return (ft_free(p, size));
		j = 0;
		while (*s && *s != c)
			p[i][j++] = *s++;
		p[i++][j] = '\0';
	}
	p[i] = NULL;
	return (p);
}
