/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 15:37:10 by abdait-m          #+#    #+#             */
/*   Updated: 2019/10/23 15:43:45 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		i;
	size_t		srclen;
	size_t		dstlen;

	if (!size && !dst)
		return (ft_strlen(src));
	srclen = ft_strlen(src);
	dstlen = ft_strlen(dst);
	i = dstlen;
	if (size < dstlen)
		return (srclen + size);
	while (i + 1 < size && *src)
	{
		dst[i++] = *src;
		src++;
	}
	if (size)
		dst[i] = '\0';
	return (dstlen + srclen);
}
