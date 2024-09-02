/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:12:49 by mkulikov          #+#    #+#             */
/*   Updated: 2024/05/06 22:56:25 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pwd(t_data *data)
{
	char	key[3] = "PWD";
	char	*pwd;
	t_env_lst	*list;
	
	list = data->lst;
	pwd = getcwd(NULL, 0);
	if(!pwd)
		return (-1);
	test_list(data->lst);
	printf("%s\n", pwd);
	while (list != NULL)
	{
		if (list->key == key)
		{
			printf("envp: %s\n", list->value);
			break;
		}
		list = list->next;
	}
	return (0);
}
