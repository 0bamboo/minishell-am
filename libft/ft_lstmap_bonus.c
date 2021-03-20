/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 12:04:34 by abdait-m          #+#    #+#             */
/*   Updated: 2019/11/01 14:44:53 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lis;
	t_list	*lis2;

	lis2 = NULL;
	while (lst)
	{
		if (!(lis = ft_lstnew((*f)(lst->content))))
		{
			ft_lstclear(&lis2, del);
			return (NULL);
		}
		ft_lstadd_back(&lis2, lis);
		lst = lst->next;
	}
	return (lis2);
}
