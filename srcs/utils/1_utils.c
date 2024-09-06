/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 11:06:10 by mkulikov          #+#    #+#             */
/*   Updated: 2024/09/04 12:54:08 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_stream_type(t_type type)
{
	if (type == RED_OUT || type == APPEND)
		return (1);
	return (0);
}

int	ft_dup2(int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
	{
		perror("dup");
		return (-1);
	}
	return (0);
}

int	ft_dup(int fd)
{
	if (dup(fd) == -1)
	{
		perror("dup");
		return (-1);
	}
	return (0);
}

int	get_size_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		i++;
	}
	return (i);
}