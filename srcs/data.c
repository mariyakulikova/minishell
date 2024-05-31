/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:29:16 by mkulikov          #+#    #+#             */
/*   Updated: 2024/05/31 14:37:10 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	data_init(t_data **data, char **envp)
{
	(*data)->orig_std_in = dup(STDIN_FILENO);
	(*data)->orig_std_out = dup(STDOUT_FILENO);
	(*data)->lst = set_envp_lst(envp);
	if (!(*data)->lst)
	{
		free(data);
		exit(EXIT_SUCCESS);
	}
	(*data)->exit_status = 0;
	(*data)->exit_status_final = 0;
	(*data)->tokens = NULL;
	(*data)->line = NULL;
	(*data)->cmd_tab = NULL;
	(*data)->path = NULL;
}


// void	init_loop(t_data *data)
// {

// }