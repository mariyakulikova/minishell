/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:24:03 by mkulikov          #+#    #+#             */
/*   Updated: 2024/08/21 16:19:49 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	str_chr_idx(const char *str, int c)
{
	int	i;

	i = 0;
	while (*(str + i))
	{
		if (*(str + i) == (char)c)
			return (i);
		i++;
	}
	return (-1);
}

int	is_space(char c)
{
	if (c == ' ' || c == '\f' || \
		c == '\n' || c == '\r' || \
		c == '\t' || c == '\v')
		return (1);
	return (0);
}

void	ft_lstadd_back_ms(t_token **lst, t_token *new)
{
	t_token	*last;

	last = ft_lstlast_ms(*lst);
	if (!last)
	{
		*lst = new;
		new->prev = NULL;
	}
	else
	{
		last->next = new;
		new->prev = last;
		new->next = NULL;
	}
}

t_token	*ft_lstlast_ms(t_token *lst)
{
	t_token	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next)
	{
		temp = temp->next;
	}
	return (temp);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (*(split + i))
	{
		free(*(split + i));
		i++;
	}
	free(split);
}
