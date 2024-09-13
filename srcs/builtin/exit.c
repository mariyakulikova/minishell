/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:14:35 by mkulikov          #+#    #+#             */
/*   Updated: 2024/09/13 16:27:04 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	valid_exit(char	**str);

int	ft_exit(t_data *data, char **cmd_tab)
{
	int	wexit;
	int	exit_status;

	(void) cmd_tab;
	wexit = get_builtin_index(data->cmd_tab, "exit");
	exit_status = 0;
	if (data->cmd_tab[wexit][1] != NULL)
	{
		exit_status = valid_exit(data->cmd_tab[wexit]);
		if (exit_status != 0)
			return (exit_status);
		exit_status = get_exit_status(ft_atoi(data->cmd_tab[wexit][1]));
	}
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

static int	valid_exit(char	**str)
{
	int	i;

	i = 0;
	while (str[1][i])
	{
		if (str[2] != NULL)
		{
			write(2, "exit : too many arguments\n", 26);
			return (1);
		}
		if (ft_isdigit(str[1][i]) == 0 && str[1][i] != '+' && str[1][i] != '-')
		{
			write(2, "exit : numeric argument required\n", 33);
			return (2);
		}
		i++;
	}
	return (0);
}
