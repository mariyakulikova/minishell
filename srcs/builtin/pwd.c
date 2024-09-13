/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:12:49 by mkulikov          #+#    #+#             */
/*   Updated: 2024/09/12 16:22:22 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pwd(t_data *data, char **cmd_tab)
{
	(void)data;
	(void)cmd_tab;
	char	*pwd;
	pwd = getcwd(NULL, 0);
	if(!pwd)
		return (-1);
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
