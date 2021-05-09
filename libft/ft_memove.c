/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memove.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 15:59:51 by abdait-m          #+#    #+#             */
/*   Updated: 2021/05/09 16:01:13 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char			*ptr;
	const char		*ptr2;

	ptr = (char *)dest;
	ptr2 = (const char *)src;
	if (!len)
		return (dest);
	if (ptr <= ptr2)
		return (ft_memcpy(ptr, ptr2, len));
	ptr += len;
	ptr2 += len;
	while (len--)
		*--ptr = *--ptr2;
	return (dest);
}
