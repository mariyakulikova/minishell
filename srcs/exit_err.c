/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_err.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:42:59 by fjoestin          #+#    #+#             */
/*   Updated: 2024/09/10 17:32:45 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit_err(char *msg, t_data *data)
{
	free_reprompt(data);
	write(2, msg, ft_strlen(msg));
	ft_minishell(data);
}