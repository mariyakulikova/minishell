/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:12:49 by mkulikov          #+#    #+#             */
/*   Updated: 2024/05/08 14:35:56 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_echo(t_data *data)
{
	int i;
	int	j;
	int	wecho;
	bool new_line;

	wecho = get_builtin_index(data->cmd_tab, "echo");
	j = 1;
	new_line = true;
	while (ft_strncmp(data->cmd_tab[wecho][j], "-n", 2) == 0)
	{
		i = 1;
		while (data->cmd_tab[wecho][j][i] == 'n')
		{
			new_line = false;
			i++;
		}
		if (data->cmd_tab[wecho][j][i] != '\0' && data->cmd_tab[wecho][j][i] != 'n')
		{
			if (j == 1)
				new_line = true;
			break;
		}
		j++;
	}
	while (data->cmd_tab[wecho][j])
	{
		printf("%s", data->cmd_tab[wecho][j]);
		if (data->cmd_tab[wecho][j + 1] != NULL)
			printf(" ");
		j++;
	}
	if (new_line == true)
	{
		printf("\n");
	}
	return (0);
}

int get_builtin_index(char ***str, char *cmd)
{
	int	i;

	i = 0;
	while (str[i][0])
	{
		if (ft_strcmp(str[i][0], cmd) == 0)
			return(i);
		i++;
	}
	return(-1);
}