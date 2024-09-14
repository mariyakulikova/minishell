/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/09/14 16:46:27 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../minishell.h"

static int	valid_exit(char	**str);

int	ft_exit(t_data *data, char **cmd_tab)
{
	int	exit_status;

	exit_status = 0;
	if (cmd_tab[1] != NULL)
	{
		exit_status = valid_exit(cmd_tab);
		if (exit_status != 0)
			return (exit_status);
		exit_status = get_exit_status(ft_atoi(cmd_tab[1]));
	}
	ft_free_data(data);
	printf("exit\n");
	exit(exit_status);
}

int	get_exit_status(int exit_status)
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
			return (err_msg("exit: too many arguments\n", 1));
		if (ft_isdigit(str[1][i]) == 0 && str[1][i] != '+' && str[1][i] != '-')
			return (err_msg("exit: numeric argument required\n", 2));
		i++;
	}
	return (0);
}
