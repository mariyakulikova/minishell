/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_err.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:42:59 by fjoestin          #+#    #+#             */
/*   Updated: 2024/09/16 12:08:33 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit_err(char *msg, t_data *data)
{
	free_reprompt(data);
	if (msg)
		write(2, msg, ft_strlen(msg));
	ft_minishell(data);
}

int	err_msg(char *msg, int code)
{
	write(2, msg, ft_strlen(msg));
	return (code);
}
