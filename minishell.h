/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:59:01 by mkulikov          #+#    #+#             */
/*   Updated: 2024/05/06 23:40:56 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include "libft/libft.h"

# define ENTRY_PROMPT "minishell$ "
# define HERE_DOC_PROMPT "> "
# define WHITE_SPACE "\f\r\v\t\n "
# define SINGLE_QUOTE 39
# define DOBLE_QUOTE 34
# define WORD 0

typedef enum e_type
{
	OPERAND,
	STRING,
	ENVAR,
	PIPE,
	HERE_DOC,
}			t_type;

typedef struct s_env_lst
{
	char				*key;
	char				*value;
	struct s_env_lst	*next;
}			t_env_lst;

typedef struct s_token
{
	char			*value;
	t_type			type;
	struct s_token	*inner;
	struct s_token	*next;
}			t_token;

typedef struct s_data
{
	t_env_lst	*lst;
	t_token	*token;
	char		**path;
	char		**cmd_tab;
	char		*prompt;
}			t_data;

/* lexer */
int			lexer(t_data *data);

/* parser */
int			parser(t_data *data);

/* executer */
int			executer(t_data *data);

/* utils/ */
int			str_chr_idx(const char *str, int c);
int			is_space(char c);

/* built-in/ */
int			ft_cd(t_data *data);
int			ft_echo(t_data *data);
int			ft_env(t_data *data);
int			ft_exit(t_data *data);
int			ft_export(t_data *data);
int			ft_pwd(t_data *data);
int			ft_unset(t_data *data);

/* envp_lst.c */
void		envp_lst_free(t_env_lst *lst);
t_env_lst	*set_env_lst(char **envp);
t_env_lst	*envp_lst_new(char *envp);

/* data.c */
void		data_init(t_data **data, char **envp);

#endif
