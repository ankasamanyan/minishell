/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 16:37:17 by wmardin           #+#    #+#             */
/*   Updated: 2022/12/21 16:37:17 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# define E_NOTVALID "not a valid identifier"
# define E_NUMARG "numeric argument required"

typedef struct s_export
{
	char	*name;
	char	*value;
	int		rank;
}	t_exp;

//cd.c
int		cd(t_cmd *cmdnode);
char	*get_homedir(char **env);
char	*build_absolutepath(char *rel_path);
void	update_pwd(t_data *data);

//echo.c
int		echo(t_cmd *cmdnode);
bool	is_onlytargetchar(char *string, char targetchar);
int		echo_builtin(t_cmd *cmd);

//env.c
int		env(t_cmd *cmdnode);
void	build_env(t_data *data, t_list *exp_list);

//exit.c
void	bltn_exit(t_cmd *cmdnode);
int		get_exitval(t_data *data, char **cmds);
bool	is_onlydigits(char *string);

//export_init.c
void	init_exportlistandenv(t_data *data, char **env);
void	increase_shlvl(t_data *data);
t_list	*get_namenode(t_list *explist, char *name);
void	print_export(t_cmd *cmdnode);

//export.c
int		export(t_cmd *cmdnode);
t_exp	*build_expnode(char *string);
int		handle_expnode(t_list *exp_list, t_exp *expnode, char *cmdstring);
void	free_expnode(t_exp *expnode);
bool	has_invalidformat(char *string);

//export_ordering.c
void	set_order(t_list *list);
void	compare_nodes(t_list *list, int i);
void	reset_rank(t_list *list);
t_list	*get_firstunranked(t_list *list);
bool	is_unrankedandprecedes(t_exp *node1, t_exp *node2);

//pwd.c
int		pwd(t_cmd *cmdnode);

//unset.c
int		unset(t_cmd *cmdnode);
void	del_fromexplist(t_list *del_node, t_list **exp_list);
t_list	*get_precedingnode(t_list *node, t_list *list);

#endif