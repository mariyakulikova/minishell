
#include "../../minishell.h"

void	free_reprompt(t_data *data)
{
	//free tokens
	free_triple_tab(data->cmd_tab, data->cmd_size);
	free_tokens(data->tokens);
	data->tokens = NULL;
	data->cmd_tab = NULL;
	// free fd list
	free_llist(data->fd_list_tab, data->cmd_size);
	data->fd_list_tab = NULL;
	free(data->prompt);
	data->prompt = NULL;
	free(data->line);
	data->line = NULL;
	// free prompt and line
}
