/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 12:36:49 by abdait-m          #+#    #+#             */
/*   Updated: 2019/10/23 15:35:03 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	*t;

	p = (unsigned char *)s1;
	t = (unsigned char *)s2;
	i = 0;
	while (p[i] != '\0' && t[i] != '\0' && i < n)
	{
		if (p[i] != t[i])
			return (p[i] - t[i]);
		i++;
	}
	if (i != n)
		return (p[i] - t[i]);
	return (0);
}
