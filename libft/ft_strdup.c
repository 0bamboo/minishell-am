/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 14:15:25 by abdait-m          #+#    #+#             */
/*   Updated: 2019/11/02 14:30:02 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
