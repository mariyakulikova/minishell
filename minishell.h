/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 10:08:07 by mkulikov          #+#    #+#             */
/*   Updated: 2024/09/17 12:50:37 by fjoestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include <signal.h>

# define ENTRY_PROMPT "minishell$ "
# define HERE_DOC_PROMPT "> "
# define WHITE_SPACE "\f\r\v\t\n "
# define SINGLE_QUOTE 39
# define DOUBLE_QUOTE 34
# define PIPE_PROMPT 124
# define TEMP_FILE "/var/tmp/.temp"

# define TRUE 1
# define FALSE 0

typedef enum e_type
{
	OPERAND,
	STRING,
	ENVAR,
	PIPE,
	HERE_DOC,
	RED,
	RED_IN,
	RED_OUT,
	APPEND
}			t_type;

typedef struct s_llist
{
	void			*key;
	void			*value;
	struct s_llist	*next;
}			t_llist;

typedef struct s_env_lst
{
	char				*key;
	char				*value;
	struct s_env_lst	*next;
}			t_env_lst;

typedef struct s_token
{
	char			*value;
	int				quotes;
	int				index;
	int				join;
	t_type			type;
	struct s_token	*prev;
	struct s_token	*next;
}			t_token;

typedef struct s_exe_data
{
	int				*pipe_tab;
	int				*fd_tab;
	pid_t			*pid_tab;
	int				pids_size;
	int				pipes_size;
}			t_exe_data;

typedef struct s_data	t_data;

typedef int				(*t_builtin_func)(t_data *, char **);

struct s_data
{
	t_env_lst		*lst;
	t_env_lst		*export_list;
	t_token			*tokens;
	int				n_tokens;
	char			***cmd_tab;
	int				cmd_size;
	t_llist			**fd_list_tab;
	char			*prompt;
	char			*line;
	int				exit_status;
	int				exit_status_final;
	int				orig_std_in;
	int				orig_std_out;
	char			*builtin_name[7];
	t_builtin_func	builtin_tab[7];
	char			**envp;
	char			*oldpwd;
};

/* lexer */
int			lexer(t_data *data);
t_token		*token_new(char *prompt, int start, int end);
int			check_single_quote(char *prompt);
int			check_double_quote(char *prompt);
int			check_word(char *prompt);
t_token		*tokenizer(t_data *data);
bool		check_open_quotes(char *prompt);
void		update_index(t_token *tokens, t_data *data);
void		processing(t_data *data);
void		update_type(t_data *data);
t_type		check_pipe(t_token *tokens, t_data *data);
void		real_pipe(t_token *token, t_data *data);
t_token		*ft_new_token(char *line, t_token **curr);
void		expander(t_token *tokens, t_data *data);
char		*expand_dollar(char *str, int *i, t_data *data);
void		check_types(t_data *data);
t_type		check_redirect(t_token *tokens, t_data *data);
int			real_red(t_token *token, int red);
int			check_prompt(char *prompt, int *start);
char		**ft_split_ms(char *prompt, int red);
char		**ft_split_red_ms(char *prompt, int wred);
t_env_lst	*new_env(char *new_key, char *new_value);
void		remove_empty_tokens(t_data *data);
int			check_redirect_helper(t_token *tokens, t_data *data,
				bool in_sq, bool in_dq);

/* parser */
int			parser(t_data *data);
char		**update_cmd(char **old_cmd, t_token *token);
bool		is_red(t_token *token);
int			add_fd_list(t_llist **fd_list, t_token **curr);

/* executer */
int			executer(t_data *data);
int			init_exe_data(t_exe_data **exe_data, t_data *data);
int			free_exe_data(t_exe_data *exe_data, int code);
void		waitpids(t_exe_data *exe_data, t_data *data);
void		execute_cmd(t_data *data, int i);
int			set_fd(int *fd, t_data *data, int i);
void		close_fd(int *fd, int size);
int			dup_fd(int *fd_tab, int j, int size);
int			handle_heredoc(t_llist *fd_list, t_data *data, int i);
char		*get_value(char *key, t_data *data);
int			link_pipes(int *pipe_tab, int size, int i);
int			reset_std(t_data *data, int *fd);
int			unlink_fd_list_tab(t_data *data);
int			execute_heredoc(t_data *data, t_exe_data *exe_data);
char		*get_fname(char *str, int i);

/* utils/ */
int			str_chr_idx(const char *str, int c);
int			is_space(char c);
void		ft_lstadd_back_ms(t_token **lst, t_token *new);
t_token		*ft_lstlast_ms(t_token *lst);
void		free_split(char **split);
t_llist		*new_llist(void *key, void *value);
void		llistadd_back(t_llist **llist, t_llist *new);
int			get_stream_type(t_type type);
int			ft_dup2(int old_fd, int new_fd);
int			ft_dup(int fd);
int			get_size_tab(char **tab);
int			get_size_tab(char **tab);

/* built-in/ */
int			ft_cd(t_data *data, char **cmd_tab);
void		ft_cd_helper(t_data *data, char *ch);
int			ft_echo(t_data *data, char **cmd_tab);
bool		ft_echo_helper(char **cmd_tab, int *j, bool new_line);
int			ft_env(t_data *data, char **cmd_tab);
int			ft_exit(t_data *data, char **cmd_tab);
int			ft_export(t_data *data, char **cmd_tab);
int			ft_pwd(t_data *data, char **cmd_tab);
int			ft_unset(t_data *data, char **cmd_tab);
int			get_builtin_idx(t_data *data, char *str);
int			get_builtin_index(char ***str, char *cmd);
void		sort_list(t_env_lst *list);
void		update_exp_list(t_env_lst *curr, char *new_key, char *new_value);
int			valid_format(char *str);
int			get_exit_status(int exit_status);

/* envp_lst.c */
void		envp_lst_free(t_env_lst *lst);
t_env_lst	*set_envp_lst(char **envp);
t_env_lst	*envp_lst_new(char *envp);
t_env_lst	*get_var_by_key(t_env_lst *envp_list, char *key);

/* data.c */
void		ft_minishell(t_data *data);
void		data_init(t_data **data, char **envp);

/* get */
int			get_if_quotes(char *value);

//exit_err
void		ft_exit_err(char *msg, t_data *data);
int			err_msg(char *msg, int code);

// free
void		ft_free_data(t_data *data);
void		free_triple_tab(char ***cmd_tab, int cmd_size);
void		free_llist(t_llist **fd_list_tab, int size);
void		free_tokens(t_token *tokens);
void		free_reprompt(t_data *data);
void		free_tab(char **tab);

// signals
void		set_signal(void);
void		signal_handler(int sig);
void		signals_non_interactive_handler(void);

#endif
