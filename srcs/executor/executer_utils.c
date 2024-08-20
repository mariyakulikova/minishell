/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:00:34 by mkulikov          #+#    #+#             */
/*   Updated: 2024/08/19 16:26:12 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	close_fd(int *fd, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		if (*(fd + i) > 2)
			close(*(fd + i));
	}
}

void	waitpids(t_exe_data *exe_data, t_data *data)
{
	int	i;

	i = 0;
	(void)data;
	while (i < exe_data->pids_size)
	{
		waitpid(*(exe_data->pids + i), NULL, 0);
		i++;
	}
}
