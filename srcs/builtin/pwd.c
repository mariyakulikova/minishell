/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:12:49 by mkulikov          #+#    #+#             */
/*   Updated: 2024/09/09 14:50:05 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pwd(t_data *data)
{
	(void)data;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if(!pwd)
		return (-1);
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
