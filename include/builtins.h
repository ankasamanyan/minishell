#ifndef BUILTINS_H
# define BUILTINS_H

# define E_NOTVALID "not a valid identifier"

typedef struct s_export
{
	char	*name;
	char	*value;
	int		rank;
}	t_exp;

//cd.c
bool	cd(t_cmd *cmdnode);
char	*get_homedir(char **env);
char	*build_absolutepath(char *rel_path);

//pwd.c
bool	pwd(t_cmd *cmdnode);

//echo.c
bool	echo(t_cmd *cmdnode);
void	echo_builtin(t_cmd *cmd);

//env.c
bool	env(t_cmd *cmdnode);
void	env_builtin(t_cmd *cmdnode);
void	build_env(t_data *data, t_list *exp_list);

//export1.c
bool	export(t_cmd *cmdnode);
t_exp	*make_expnode(char *string);
void	handle_expnode(t_list *exp_list, t_exp *expnode, char *cmdstring);
bool	has_invalidformat(char *string);
t_list	*get_samename(t_list *list, char *name);

//export2.c
void	build_exportlistfromenv(t_data *data);
void	set_order(t_list *list);
void	reset_rank(t_list *list);
t_list	*get_firstunranked(t_list *list);
bool	is_unrankedandprecedes(t_exp *node1, t_exp *node2);

<<<<<<< HEAD
=======
//export3.c
void	print_export(t_list *list);

//unset.c
bool	unset(t_cmd *cmdnode);
void	del_fromexplist(t_list *del_node, t_list *exp_list);
t_list	*get_precedingnode(t_list *node, t_list *list);
>>>>>>> parsing_03

#endif