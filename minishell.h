#ifndef MINISHELL_H
# define MINISHELL_H

# include "pipex.h"
# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT "[minishell]$ "
# define HERE_DOC_PROMPT "> "
# define WHITE_SPACE "\f\r\v\t\n "
# define SINGLE_QUOTE 39
# define DOUBLE_QUOTE 34

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
	int				quotes;
	int				index;
	int				join;
	t_type			type;
	struct s_token	*prev;
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

// env_lst
void	envp_lst_free(t_env_lst *lst);
t_env_lst	*envp_lst_new(char *envp);
t_env_lst	*set_env_lst(char **envp);

// data
void	init_data(t_data **data, char **envp);

//utils_1
int	str_chr_idx(const char *str, int c);

#endif
