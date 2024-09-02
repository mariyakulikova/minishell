/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:14:35 by mkulikov          #+#    #+#             */
/*   Updated: 2024/05/06 22:56:21 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_exit(t_data *data)
{
	int	wexit;
	int	exit_status;
	printf("here is exit\n");
	wexit = get_builtin_index(data->cmd_tab, "exit");
	exit_status = 0;
	if (wexit == -1 || data->cmd_tab[wexit][1] == NULL)
	{
		ft_free_data(data);
		printf("exit\n");
		return (exit_status);
	}
	if (data->cmd_tab[wexit][2] != NULL)
	{
		write(2, "exit: Too many arguments\n", 26);
		return (2);
	}
	while (data->cmd_tab[wexit][1][exit_status])
	{
		if (ft_isdigit(data->cmd_tab[wexit][1][exit_status]) == 0)
		{
			write(2, "exit: Numeric argument required\n", 33);
			return(2);
		}
		exit_status++;
	}
	exit_status = get_exit_status(ft_atoi(data->cmd_tab[wexit][1]));
	ft_free_data(data);
	printf("exit\n");
	exit(exit_status);
}

int	get_exit_status(int	exit_status)
{
	if (exit_status < 0)
		exit_status = 256 + (exit_status % 256);
	else if (exit_status > 256)
		exit_status = exit_status % 256;
	return (exit_status);
}