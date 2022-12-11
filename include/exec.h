#ifndef EXEC_H
# define EXEC_H

# include "../include/minishell.h"
// # include " src/../include/../include/minishell.h"

typedef struct s_data	t_data;
typedef struct s_cmd	t_cmd;

/* my additional Libft functions, because Wolf decided to use his Libft as submodule */
void	ft_free_array(char **array);
char	*ft_triple_strjoin(char *first, char *second, char *third);
void	print_2d_array(char	**arr, int fd);
/* command execution */
void	exec(void *cmd_list);
/* input fd configuration */
void	input_files(void *input);
void	if_no_input(t_cmd *cmd);
/* output fd configuration */
void	output_files(void *output);
void	if_no_output(t_cmd *cmd);
/* path manipulations */
void	search_path_env(t_cmd *cmd);
void	find_cmd_path(t_cmd *cmd);
/* I have no clue actually */
void	onexit(t_data *data);
/* builtin thingy */
void	if_builtins(t_cmd *cmd);
/* ze pipes */
void	close_them_all(t_cmd *cmd);



#endif