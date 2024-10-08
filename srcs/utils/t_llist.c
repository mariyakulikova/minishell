/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_llist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:59:03 by mkulikov          #+#    #+#             */
/*   Updated: 2024/09/02 20:59:21 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_llist	*new_llist(void *key, void *value)
{
	t_llist	*new;

	new = (t_llist *)malloc(sizeof(t_llist));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	llistadd_back(t_llist **llist, t_llist *new)
{
	t_llist	*last;

	if (NULL == llist)
		return ;
	if (NULL == *llist)
	{
		*llist = new;
		return ;
	}
	last = *llist;
	while (last->next)
		last = last->next;
	last->next = new;
}
