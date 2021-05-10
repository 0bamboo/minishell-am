/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majermou <majermou@students.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 13:13:00 by majermou          #+#    #+#             */
/*   Updated: 2021/05/10 13:13:03 by majermou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstrs(char *str)
{
	if (str)
	{
		write(1, str, ft_strlen(str));
		return (ft_strlen(str));
	}
	return (0);
}
