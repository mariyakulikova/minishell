/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:54:22 by mkulikov          #+#    #+#             */
/*   Updated: 2024/02/22 10:57:22 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*node;
	t_list	*tmp;

	if (!lst || !f || !del)
		return (NULL);
	head = NULL;
	tmp = lst;
	while (tmp)
	{
		node = ft_lstnew(f(lst->content));
		ft_lstadd_back(&head, node);
		if (!node)
		{
			ft_lstclear(&head, del);
			return (NULL);
		}
		tmp = tmp->next;
	}
	return (head);
}
