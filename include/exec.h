#ifndef EXEC_H
# define EXEC_H

# include "../include/minishell.h"
// # include " src/../include/../include/minishell.h"

// typedef struct s_data	t_data;

typedef struct s_exec
{
	struct t_data		*data;
	char				**env;
	char				*big_path;
	char				*full_path;
	int					pipe[2];
	int					temp_pipe;

}	t_exec;

#endif