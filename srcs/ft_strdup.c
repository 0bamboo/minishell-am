/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 14:15:25 by abdait-m          #+#    #+#             */
/*   Updated: 2021/03/16 22:17:48 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strdup(const char *s)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	len = ft_strlen(s);
	if (!(tmp = (char *)malloc(len + 1)))
		return (0);
	while (i <= len)
	{
		tmp[i] = s[i];
		i++;
	}
	return (tmp);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	j;
	size_t	size;

	j = 0;
	if (!s)
		return (NULL);
	if (!s[start])
		return (ft_strdup(""));
	size = ft_strlen(s);
	if (len > size)
		len = size;
	if (!(ptr = (char *)malloc((len + 1) * sizeof(char))))
		return (NULL);
	if (start < size)
	{
		while (j < len && s[start] != '\0')
		{
			ptr[j++] = s[start++];
		}
	}
	ptr[j] = '\0';
	return (ptr);
}
