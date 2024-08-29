/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 16:26:54 by mkulikov          #+#    #+#             */
/*   Updated: 2024/08/29 11:31:33 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	link_pipes(int *pipe_tab, int *fd_tab, int size, int i)
{
	(void)fd_tab;
	if (i == 0)
	{
		close(pipe_tab[0]);
		dup2(pipe_tab[1], STDOUT_FILENO);
		close(pipe_tab[1]);
	}
	else if (i == size - 1)
	{
		close(pipe_tab[2 * i - 1]);
		dup2(pipe_tab[2 * i - 2], STDIN_FILENO);
		close(pipe_tab[2 * i - 2]);
	}
	else
	{
		dup2(pipe_tab[2 * i + 1], STDOUT_FILENO);
		dup2(pipe_tab[2 * i - 2], STDIN_FILENO);
		close(pipe_tab[2 * i + 1]);
		close(pipe_tab[2 * i - 2]);
	}
	return (0);
}
