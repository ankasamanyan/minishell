#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include "exec.h"

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

# define READ_PIPE	0
# define WRITE_PIPE	1

typedef struct s_cmd	t_cmd;

typedef struct s_list
{
	void				*content;
	struct s_list		*next;
}	t_list;

typedef struct s_cmd
{
	char				**cmd_arr;
	t_list				*input;
	t_list				*output;
}	t_cmd;

typedef struct s_redir_pair
{
	bool		key;		// (< || <<) && (>> || >)
	char		*value;		// file || here_doc
}	t_redir_pair;

typedef struct s_data
{
	t_list		cmd_list;
}		t_data;


#endif