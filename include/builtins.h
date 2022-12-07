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

//env.c
bool	env(t_cmd *cmdnode);

//export1.c
bool	export(t_cmd *cmdnode);
bool	has_invalidformat(char *string);
void	print_export(t_list *list);
void	reset_rank(t_list *list);
//export1.c


#endif