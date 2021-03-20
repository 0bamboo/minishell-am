/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 12:41:44 by abdait-m          #+#    #+#             */
/*   Updated: 2019/10/23 15:57:56 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			if_long(long a, int sign)
{
	if (a > 0 && sign < 0)
		return (0);
	if (a < 0 && sign > 0)
		return (-1);
	return (a);
}

int			ft_atoi(const char *str)
{
	int		i;
	long	a;
	int		sign;

	a = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' ||
			str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		i++;
		sign = -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		a = (a * 10) + str[i] - 48;
		i++;
	}
	a = a * sign;
	return (if_long(a, sign));
}
