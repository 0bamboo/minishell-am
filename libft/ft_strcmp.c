/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 10:37:55 by abdait-m          #+#    #+#             */
/*   Updated: 2021/03/31 10:38:51 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	*t;

	p = (unsigned char *)s1;
	t = (unsigned char *)s2;
	i = 0;
	while (p[i] != '\0' && t[i] != '\0')
	{
		if (p[i] != t[i])
			return (p[i] - t[i]);
		i++;
	}
	return (p[i] - t[i]);
}
