#include "../../include/minishell.h"

void	if_builtins(t_cmd *cmd)
{
	if (ft_strncmp(cmd->cmd_arr[0], "export", ft_strlen("export")) == 0)
		export(cmd);
	else if (ft_strncmp(cmd->cmd_arr[0], "env", ft_strlen("env")) == 0)
		env_builtin(cmd);
	else if (ft_strncmp(cmd->cmd_arr[0], "pwd", ft_strlen("pwd")) == 0)
		pwd(cmd);
	else if (ft_strncmp(cmd->cmd_arr[0], "cd", ft_strlen("cd")) == 0)
		cd(cmd);
	else if (ft_strncmp(cmd->cmd_arr[0], "echo", ft_strlen("echo")) == 0)
		echo_builtin(cmd);
	// else if (ft_strncmp(cmd->cmd_arr[0], "unset", ft_strlen("unset")) == 0)
	// 	unset(cmd);
}
