/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 18:17:47 by majermou          #+#    #+#             */
/*   Updated: 2021/03/13 22:19:39 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int						check_break_line(char *tab)
{
	int					i;

	i = 0;
	while (*tab)
		if (*tab++ == '\n')
			i++;
	return (i);
}

int						ft_strlen(const char *str)
{
	int					n;

	n = 0;
	while (*str && *str != '\n')
	{
		str++;
		n++;
	}
	return (n);
}

int						check_previous_read(char **line, char *tab)
{
	int					i;
	char				*tmp;

	i = 0;
	while (tab[i] != '\n')
		i++;
	tab[i++] = '&';
	tmp = *line;
	if (!(*line = ft_strjoin(*line, tab + i)))
		return (0);
	free(tmp);
	return (1);
}

char					*ft_strjoin(char const *line, char const *tab)
{
	char				*ptr;
	char				*tmp;

	if (!(ptr = (char*)malloc(ft_strlen(line) + ft_strlen(tab) + 1)))
		return (NULL);
	tmp = ptr;
	while (*line)
		*ptr++ = *line++;
	while (*tab && *tab != '\n')
		*ptr++ = *tab++;
	*ptr = '\0';
	return (tmp);
}

void					for_next_read(char **tab)
{
	int					i;
	int					j;

	i = 0;
	j = 0;
	if (!check_break_line(*tab))
		tab[0][0] = '\0';
	else
	{
		while (tab[0][i] != '\n')
			i++;
		if (tab[0][i + 1] != '\n')
			i++;
		while (tab[0][i])
			tab[0][j++] = tab[0][i++];
		tab[0][j] = '\0';
	}
}
