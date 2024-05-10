/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:31:50 by mkulikov          #+#    #+#             */
/*   Updated: 2024/03/26 15:27:47 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include "libft.h"

# define BUFF_SIZE 10
# define TMP_FILE ".temp"
# define ERR_ARGS "Invalid number of arguments\n"
# define ERR_PIPE "Pipe error"
# define ERR_DUP2 "Dup2 error"
# define ERR_FORK "Fork error"
# define ERR_EXEC "Execve error"
# define ERR_OPEN "File opening error"
# define ERR_READ "Reading error"
# define ERR_CMD "command not found"
# define ERR_SPLT "Split error"
# define ERR_ENVP "envp is NULL"

typedef struct s_param {
	pid_t	*pids;
	int		*pipes;
	char	*path;
	char	**cmds_path;
	char	***cmds;
	char	**envp;
	int		infile_fd;
	int		outfile_fd;
	int		cmd_num;
	int		pipes_size;
	int		here_doc;
	char	*limiter;
}			t_param;

t_param	*param_init(void);
void	set_param(t_param *param, int argc, char **argv, char **envp);
void	free_param(t_param *params);
void	free_split(char **split);
void	my_exit(t_param *params, char *str, char *name);
void	open_files(char *infile, char *outfile, t_param *params);
void	parse_cmds(t_param *params, int argc, char **argv);
void	set_path_value(t_param *params, char **envp);
char	*get_cmd_path(char **cmds_path, char *cmd);
void	waitpids(t_param *param, int size);
void	close_pipes(t_param *param);
void	child(t_param *param, int i);
int		here_doc(t_param *param);
void	close_files(t_param *param);

#endif
