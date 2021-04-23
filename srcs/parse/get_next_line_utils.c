/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 18:17:47 by majermou          #+#    #+#             */
/*   Updated: 2021/04/22 23:57:23 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	len_if(char *s, int nl)
{
	size_t	l;

	l = 0;
	if (!nl)
		while (s[l])
			l++;
	else
		while (s[l] && s[l] != '\n')
			l++;
	return (l);
}

char	*ft_dup_free(char *src, char **to_free)
{
	int		l;
	int		i;
	char	*dup;

	if ((l = len_if(src, 0)) == 0)
	{
		if (*to_free)
		{
			free(*to_free);
			*to_free = NULL;
		}
		return (NULL);
	}
	if (!(dup = (char*)malloc(sizeof(char) * (l + 1))))
		return (NULL);
	i = -1;
	while (++i < l)
		dup[i] = src[i];
	dup[i] = '\0';
	if (*to_free)
	{
		free(*to_free);
		*to_free = NULL;
	}
	return (dup);
}

int		build_line(char **line, char **buff, char **buff_s, char step)
{
	char	*tmp;
	char	*par;

	if (step == 0)
		par = *buff_s;
	else
		par = *buff;
	tmp = ft_strjoin(*line, par);
	free(*line);
	*line = tmp;
	if ((tmp = ft_strchr(par, '\n')) != NULL)
	{
		if (step == 0)
		{
			*buff_s = ft_dup_free(tmp + 1, buff_s);
			free(*buff);
		}
		else if (step == 1)
			*buff_s = ft_dup_free(tmp + 1, buff);
		return (1);
	}
	free(*buff_s);
	*buff_s = NULL;
	return (0);
}
