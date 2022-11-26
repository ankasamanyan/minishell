#ifndef EXEC_H
# define EXEC_H

# include "../include/minishell.h"
// # include " src/../include/../include/minishell.h"

typedef struct s_data	t_data;
typedef struct s_cmd	t_cmd;

/* my additional Libft functions, because Wolf decided to use his Libft as submodule */
void	ft_free_array(char **array);
char	*ft_triple_strjoin(char *first, char *second, char *third);
/* command execution */
void	exec(void *cmd_list);
void	input_files(void *input);
void	if_no_input(t_cmd *cmd);
void	output_files(void *output);
void	if_no_output(t_cmd *cmd);

/* path manipulations */
void	search_path_env(t_cmd *cmd);
void	find_cmd_path(char *big_path, t_data *data);


#endif