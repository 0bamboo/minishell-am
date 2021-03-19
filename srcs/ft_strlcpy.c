/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 11:56:45 by abdait-m          #+#    #+#             */
/*   Updated: 2021/03/16 22:14:55 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t		i;
	size_t		len;
	size_t		max;
	char		*d;

	i = 0;
	if (!src)
		return (0);
	d = dst;
	max = size - 1;
	len = ft_strlen(src);
	if (size == 0)
		return (len);
	while (src[i] != '\0' && max > 0)
	{
		d[i] = src[i];
		i++;
		max--;
	}
	d[i] = '\0';
	return (len);
}
