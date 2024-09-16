/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:27:12 by fjoestin          #+#    #+#             */
/*   Updated: 2024/09/16 14:58:53 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	signal_handler(int sig)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void)sig;
}

void	set_signal(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

static void	display_new_line(int sig)
{
	if (sig == SIGQUIT)
		write(STDERR_FILENO, "Quit (core dumped)", 19);
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
}

void	signals_non_interactive_handler(void)
{
	signal(SIGINT, display_new_line);
	signal(SIGQUIT, display_new_line);
}
