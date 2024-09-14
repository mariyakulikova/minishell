/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:13:21 by mkulikov          #+#    #+#             */
/*   Updated: 2024/09/14 01:06:54 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_cd(t_data *data, char **cmd_tab)
{
	int		i;
	char	*ch;

	i = 1;
	if (cmd_tab[i] == NULL || ft_strcmp(cmd_tab[i], "˜") == 0)
		ch = ft_strdup(get_value("HOME", data));
	else if (ft_strcmp(cmd_tab[i], "-") == 0)
	{
		ch = ft_strdup(data->oldpwd);
		printf("%s\n", data->oldpwd);
	}
	else if (cmd_tab[2] != NULL)
		return (err_msg("cd: Too many arguments\n", 1));
	else
		ch = ft_strdup(cmd_tab[i]);
	free(data->oldpwd);
	data->oldpwd = getcwd(NULL, 0);
	if (chdir(ch) == -1)
	{
		free(ch);
		return (err_msg("cd: No such file or directory\n", 1));
	}
	else
		ft_cd_helper(data, ch);
	return (0);
}

void	ft_cd_helper(t_data *data, char *ch)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	update_env_list(data->lst, "PWD", new_pwd);
	update_env_list(data->lst, "OLDPWD", data->oldpwd);
	update_exp_list(data->export_list, "PWD", new_pwd);
	update_exp_list(data->export_list, "OLDPWD", data->oldpwd);
	free(ch);
	free(new_pwd);
}

void	update_env_list(t_env_lst *curr, char *new_key, char *new_value)
{
	bool		found;
	t_env_lst	*new;

	found = false;
	while (curr->next != NULL)
	{
		if (ft_strcmp(curr->key, new_key) == 0)
		{
			found = true;
			free(curr->value);
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
