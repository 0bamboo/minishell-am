/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 14:51:00 by abdait-m          #+#    #+#             */
/*   Updated: 2021/05/07 16:35:27 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	_ret_(int start, int len, int l)
{
	if (len > (l - start))
		return (l - start);
	else
		return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*substr;
	char		*tmp;
	size_t		l;
	size_t		i;

	if (!s)
		return (NULL);
	substr = NULL;
	l = ft_strlen(s);
	if (start < l)
	{
		len = _ret_(start, len, l);
		substr = (char *)malloc(sizeof(char) * (len + 1));
		if (!substr)
			return (NULL);
		tmp = (char *)s + start;
		i = -1;
		while (++i < len && tmp[i])
			substr[i] = tmp[i];
		substr[i] = '\0';
		return (substr);
	}
	return (ft_strdup(""));
}
