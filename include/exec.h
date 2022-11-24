#ifndef EXEC_H
# define EXEC_H

# include "../include/minishell.h"
// # include " src/../include/../include/minishell.h"

// typedef struct s_data	t_data;

typedef struct s_exec
{
	struct t_data		*data;
	char				*big_path;
	char				*full_path;
	int					pid;
	// int					pipe[2];
	// int					temp_pipe;

}	t_exec;

/* my additional Libft functions, because Wolf decided to use his Libft as submodule */
void	ft_free_array(char **array);
char	*ft_triple_strjoin(char *first, char *second, char *third);
/* command execution */
void	*exec(void *cmd_list);
void	*input_files(void *input);
void	*output_files(void *output);



#endif