/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 18:12:15 by abdait-m          #+#    #+#             */
/*   Updated: 2019/10/31 20:30:41 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **alst, void (*del)(void *))
{
	t_list *prev;
	t_list *curr;

	curr = *alst;
	while (curr)
	{
		prev = curr;
		(*del)(prev->content);
		curr = curr->next;
		free(prev);
	}
	*alst = NULL;
}
