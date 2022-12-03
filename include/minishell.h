#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>

# include "exec.h"
# include "../src/libft/include/libft.h"
# include "parsing.h"
# include "signals.h"
# include "builtins.h"

# define RESET		"\033[0m"
# define BLACK		"\033[0;30m"
# define RED		"\033[0;31m"
# define GREEN		"\033[0;32m"
# define YELLOW		"\033[0;33m"
# define PURPLE		"\033[0;34m"
# define PINK		"\033[0;35m"
# define SKY		"\033[0;36m"

# define ON_RED 	"\033[41m"
# define ON_PURPLE	"\033[44m"
# define ON_PINK	"\033[45m"

# define READ_END	0
# define WRITE_END	1

typedef struct s_data	t_data;

typedef struct s_cmd
{
	char				**cmd_arr;
	t_list				*inputlist;
	t_list				*outputlist;
	int					fd_in;
	int					fd_out;
	t_data				*data;
}	t_cmd;

typedef struct s_pair
{
	bool				doublebracket;
	char				*string;
	t_cmd				*cmd;
}	t_pair;

typedef struct s_data
{
	t_list				*cmd_list; //t_cmd as content
	t_par				parsing_struct;
	char				**env;
	int					temp_pipe;
	int					pipe[2];
	int					first_cmd; // init it to 0
	char				*big_path;
	char				*full_path;
	int					pid;
	bool				first;	//init to true; or 1;
	int					cmd_count;	//init it to 0
	char				exitcode; //innit it to 0
	char				*shell_lvl;
}		t_data;

bool	specialcase(t_data *data, char *input);
void	init_datastruct(t_data *d, char **env);

#endif