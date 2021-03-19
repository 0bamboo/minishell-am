/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 18:17:27 by majermou          #+#    #+#             */
/*   Updated: 2021/03/12 16:11:52 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char					*ft_strdup(const char *src)
{
	int			i;
	char		*str;

	i = 0;
	if (!(str = (char*)malloc(sizeof(char) * (ft_strlen(src) + 1))))
		return (NULL);
	while (i < ft_strlen(src))
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int						error_check(int fd, char **line, char **tab)
{
	if (!line || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (0);
	*line = ft_strdup("");
	if (!*tab)
	{
		if (!(*tab = (char*)malloc(BUFFER_SIZE + 1)))
			return (0);
		**tab = '\0';
	}
	return (1);
}

int						dealocate(char **line, char **tab, int ret, int var_bol)
{
	if (!*line[0] && !var_bol && check_break_line(*tab) > 1)
		if (!(check_previous_read(line, *tab)))
			return (-1);
	if (!ret && !check_break_line(*tab))
	{
		free(*tab);
		*tab = 0;
		return (0);
	}
	for_next_read(tab);
	return (1);
}

int						get_next_line(int fd, char **line)
{
	static char			*tab;
	char				*tmp;
	int					ret;
	int					var_bol;

	var_bol = 0;
	ret = 1;
	if (!error_check(fd, line, &tab))
		return (-1);
	while (1)
	{
		tmp = *line;
		if (!(*line = ft_strjoin(*line, tab)))
			return (-1);
		free(tmp);
		if (!ret || check_break_line(tab) >= 1)
			break ;
		if ((ret = read(fd, tab, BUFFER_SIZE)) == -1)
			return (-1);
		tab[ret] = '\0';
		var_bol = 1;
	}
	return (dealocate(line, &tab, ret, var_bol));
}
