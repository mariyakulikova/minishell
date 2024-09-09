/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:29:16 by mkulikov          #+#    #+#             */
/*   Updated: 2024/09/09 14:44:37 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	set_builtin_ptr(char **name, t_builtin_func *tab)
{
	name[0] = "cd";
	name[1] = "echo";
	name[2] = "env";
	name[3] = "exit";
	name[4] = "export";
	name[5] = "pwd";
	name[6] = "unset";
	tab[0] = &ft_cd;
	tab[1] = &ft_echo;
	tab[2] = &ft_env;
	tab[3] = &ft_exit;
	tab[4] = &ft_export;
	tab[5] = &ft_pwd;
	tab[6] = &ft_unset;
}

void	data_init(t_data **data, char **envp)
{
	set_builtin_ptr((*data)->builtin_name, (*data)->builtin_tab);
	(*data)->orig_std_in = dup(STDIN_FILENO);
	(*data)->orig_std_out = dup(STDOUT_FILENO);
	(*data)->lst = set_envp_lst(envp);
	(*data)->export_list = set_envp_lst(envp);
	if (!(*data)->lst)
	{
		free(data);
		exit(EXIT_SUCCESS);
	}
	(*data)->exit_status = 0;
	(*data)->exit_status_final = 0;
	(*data)->tokens = NULL;
	(*data)->cmd_tab = NULL;
	(*data)->line = NULL;
	(*data)->envp = envp;
	(*data)->fd_list_tab = NULL;
	(*data)->oldpwd = NULL;
}
