/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_err.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:42:59 by fjoestin          #+#    #+#             */
/*   Updated: 2024/08/02 16:07:42 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit_err(char *msg, t_data *data)
{
	//if data
	//reiniciar values of data
	write(2,msg, ft_strlen(msg));
	ft_minishell(data);
}