/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:13:21 by mkulikov          #+#    #+#             */
/*   Updated: 2024/09/10 18:39:08 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_cd(t_data *data)
{
	int wcd;
	int	i;
	char	*ch;
	char	*new_pwd;

	wcd = get_builtin_index(data->cmd_tab, "cd");
	i = 1;
	if (data->cmd_tab[wcd][i] == NULL || ft_strcmp(data->cmd_tab[wcd][i], "˜") == 0) // if there are no args
		ch = get_value("HOME", data);
	else if (ft_strcmp(data->cmd_tab[wcd][i], "-") == 0)
	{
		ch = data->oldpwd;
		printf("%s\n", data->oldpwd);
	}
	else if (data->cmd_tab[wcd][2] != NULL)
	{
		write(2, "cd: Too many arguments\n", 24);
		return (1);
	}
	else
		ch = data->cmd_tab[wcd][i];
	data->oldpwd = getcwd(NULL, 0);
	if (chdir(ch) == -1)
	{
		write(2, "cd: No such file or directory\n", 31);
		return (1);
	}
	else
	{
		new_pwd = getcwd(NULL, 0);
		update_env_list(data->lst, "PWD", new_pwd);
		update_env_list(data->lst, "OLDPWD", data->oldpwd);
		update_exp_list(data->export_list, "PWD", new_pwd);
		update_exp_list(data->export_list, "OLDPWD", data->oldpwd);
		free(new_pwd);
	}
	return (0);
}

void	update_env_list(t_env_lst *curr, char *new_key, char *new_value)
{
	//check if exists
	//if doesn't create a new one and add to the bottom
	bool	found;
	t_env_lst	*new;

	found = false;
	while (curr->next != NULL)
	{
		if (ft_strcmp(curr->key, new_key) == 0)
		{
			found = true;
			curr->value = ft_substr(new_value, 0, ft_strlen(new_value));
		}
		curr = curr->next;
	}
	if (found == false)
	{
		new = (t_env_lst *)malloc(sizeof(t_env_lst));
		new->key = ft_substr(new_key, 0, ft_strlen(new_key));
		new->value = ft_substr(new_value, 0, ft_strlen(new_value));
		new->next = NULL;
		curr->next = new;
	}
}
