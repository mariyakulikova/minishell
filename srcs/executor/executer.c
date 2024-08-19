/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 11:58:26 by mkulikov          #+#    #+#             */
/*   Updated: 2024/08/19 12:47:17 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"



int	executer(t_data *data)
{
	t_exe_data *exe_data;

	exe_data = NULL;
	if (init_exe_data(&exe_data, data))
		return (free_exe_data(exe_data, 1));
	(void)data;

	return (free_exe_data(exe_data, 0));
}
