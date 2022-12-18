#ifndef EXEC_H
# define EXEC_H

# include "../include/minishell.h"

typedef struct s_data	t_data;
typedef struct s_pair	t_pair;
typedef struct s_cmd	t_cmd;

/* my additional Libft functions, because Wolf decided to use his Libft as submodule */
void	ft_free_array(char **array);
void	print_2d_array(char	**arr, int fd);
char	*ft_triple_strjoin(char *first, char *second, char *third);
/* command execution */
void	exec(void *cmd_list);
void	pipex(t_cmd *cmd);
void	kiddi_process(t_cmd *cmd);
void	close_them_all(t_cmd *cmd);
/* input fd configuration */
void	if_no_input(t_cmd *cmd);
void	input_files(void *input);
void	here_doc(t_pair *input);
/* output fd configuration */
void	if_no_output(t_cmd *cmd);
void	output_files(void *output);
/* path manipulations */
void	find_cmd_path(t_cmd *cmd);
void	search_path_env(t_cmd *cmd);
void	path_access(t_cmd *cmd, char **smoll_pathsies);
/* I have no clue actually */
void	onexit(t_data *data);
/* builtin thingy */
void	builtins_exec(t_cmd *cmd);
/* error message */
void	err_msg(char *stringy);
void	err_cmd_not_found(char *stringy, int nbr);



#endif