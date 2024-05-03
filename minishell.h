/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:59:01 by mkulikov          #+#    #+#             */
/*   Updated: 2024/05/03 14:09:10 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include "libft.h"

typedef struct s_envp_lst
{
	char				*key;
	char				*value;
	struct s_envp_lst	*next;
}			t_envp_lst;

typedef struct s_data
{
	t_envp_lst	*lst;
	char		**path;
	char		*promt;
}			t_data;

/* built-in */
int	ft_cd(t_data *data);
int	ft_echo(t_data *data);
int	ft_env(t_data *data);
int	ft_exit(t_data *data);
int	ft_export(t_data *data);
int	ft_pwd(t_data *data);
int	ft_unset(t_data *data);

/* envp_lst.c */
t_envp_lst	*set_envp_lst(char **envp);

/* data.c */
void		data_init(t_data **data, char **envp);


#endif

