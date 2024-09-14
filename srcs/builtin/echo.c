/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:12:49 by mkulikov          #+#    #+#             */
/*   Updated: 2024/09/12 20:27:01 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_echo(t_data *data, char **cmd_tab)
{
	int		j;
	bool	new_line;

	(void)data;
	j = 1;
	new_line = true;
	if (cmd_tab[j] != NULL)
	{
		new_line = ft_echo_helper(cmd_tab, &j, new_line);
		while (cmd_tab[j])
		{
			printf("%s", cmd_tab[j]);
			if (cmd_tab[j + 1] != NULL)
				printf(" ");
			j++;
		}
	}
	if (new_line == true)
	{
		printf("\n");
	}
	return (0);
}

bool	ft_echo_helper(char **cmd_tab, int *j, bool new_line)
{
	int	i;

	while (cmd_tab[*j] != NULL && ft_strncmp(cmd_tab[*j], "-n", 2) == 0)
	{
		i = 1;
		while (cmd_tab[*j][i] == 'n')
		{
			new_line = false;
			i++;
		}
		if (cmd_tab[*j][i] != '\0' && cmd_tab[*j][i] != 'n')
		{
			if (*j == 1)
				new_line = true;
			break ;
		}
		(*j)++;
	}
	return (new_line);
}

int	get_builtin_index(char ***str, char *cmd)
{
	int	i;

	i = 0;
	while (str[i][0])
	{
		if (ft_strcmp(str[i][0], cmd) == 0)
			return (i);
		i++;
	}
	return (-1);
}
