#ifndef MINISHELL_H
# define MINISHELL_H

/*
# minishell

<img width="730" alt="image" src="https://user-images.githubusercontent.com/89840461/205446900-ba137aab-9ce3-487b-998c-c36f306957fc.png">


if ! [ -r $HOME/goinfre/.brew/Cellar/readline ]; then
	rm -rf $HOME/goinfre/.brew

	git clone --depth=1 https://github.com/Homebrew/brew $HOME/goinfre/.brew

	echo 'export PATH=$HOME/goinfre/.brew/bin:$PATH' >> $HOME/.zshrc

	source $HOME/.zshrc && brew update

	brew install readline
fi
*/

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
// # define ON_SKY		"\033[36m"

# define READ_END	0
# define WRITE_END	1

# define STOP ;

typedef struct s_data	t_data;

typedef struct s_cmd
{
	char				**cmd_arr;
	t_list				*inputlist;
	t_list				*outputlist;
	int					fd_in;
	int					fd_out;
	t_data				*data;
	bool				builtin;
}	t_cmd;

typedef struct s_pair
{
	bool				doublebracket;
	char				*string;
	t_cmd				*cmd;
}	t_pair;

typedef struct s_data
{
	t_list			*cmd_list;
	t_list			*exp_list;
	t_par			parsing_struct;
	char			**env;
	int				temp_pipe;
	int				pipe[2];
	int				first_cmd;
	char			*big_path;
	char			*full_path;
	int				pid;
	bool			first;
	int				cmd_count;
	int				exitcode;
	char			*shell_lvl;
}		t_data;

bool	specialcase(t_data *data, char *input);
void	init_datastruct(t_data *d, char **env);
char	**replace_env(char **env);
void	build_exportlistfromenv(t_data *data);
void	set_order(t_list *list);
t_list	*get_firstunranked(t_list *list);
bool	is_unrankedandprecedes(t_exp *node1, t_exp *node2);

#endif