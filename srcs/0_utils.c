/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:24:03 by mkulikov          #+#    #+#             */
/*   Updated: 2024/05/07 15:38:46 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

	last = ft_lstlast_ps(*lst);
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
