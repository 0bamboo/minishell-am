/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 18:07:29 by abdait-m          #+#    #+#             */
/*   Updated: 2019/11/01 14:39:49 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *t;

	t = *alst;
	if (*alst == NULL)
	{
		*alst = new;
		return ;
	}
	while (t->next)
		t = t->next;
	t->next = new;
}
