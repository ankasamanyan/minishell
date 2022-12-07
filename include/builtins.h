#ifndef BUILTINS_H
# define BUILTINS_H

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

//env.c
bool	env(t_cmd *cmdnode);

//export.c
bool	export(t_cmd *cmdnode);
void	replace_env(t_data *data);
void	build_exportlist(t_data *data);
void	set_order(t_list *list);
t_list	*get_firstunranked(t_list *list);
void	print_export(t_list *list);
bool	is_unrankedandprecedes(t_exp *node1, t_exp *node2);

#endif