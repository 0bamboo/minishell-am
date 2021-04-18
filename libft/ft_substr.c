/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 14:51:00 by abdait-m          #+#    #+#             */
/*   Updated: 2021/04/18 04:44:30 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
		len = (len > (l - start)) ? (l - start) : len;
		if (!(substr = (char *)malloc(sizeof(char) * (len + 1))))
			return (NULL);
		tmp = (char *)s + start;
		i = 0;
		while (i < len && tmp[i])
		{
			substr[i] = tmp[i];
			i++;
		}
		substr[i] = '\0';
		return (substr);
	}
	return (ft_strdup(""));
}
