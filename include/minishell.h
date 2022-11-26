#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include "../include/exec.h"
# include "../src/libft/libft.h"
# include <readline/readline.h>
// # include <readline/history.h>

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
	int					in_fd; //innit to 0
	int					out_fd; //innit to 1 plz
	char				**cmd_arr;
	t_list				*input;
	t_list				*output;
	t_data				*data;
	// int					pipe_in; // in end of while loop you set cmd.next.pipe_in to pipe[read] // in listiter for input you pit address of this and close it then open fd and store it in address
}	t_cmd;

typedef struct s_pair
{
	bool				second_sign;		// (< || <<) && (>> || >)
	char				*filename;			// file || here_doc
	t_cmd				*cmd;
}	t_pair;

typedef struct s_data
{
	t_list				*cmd_list; //t_cmd as content
	char				**env;
	int					pipe[2];
	int					first_cmd; // init it to 0
	char				*big_path;
	char				*full_path;
	int					pid;
	bool				first;	//init to true; or 1;
	int					cmd_count;	//init it to 0 
	// t_exec				*exec;
	// int					temp_pipe
	// char		*big_path;
}		t_data;


#endif