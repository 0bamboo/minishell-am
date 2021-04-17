#include "minishell.h"

char	*get_env_val(t_envlist *envlist, char *var)
{
	int		index;
	int		k;

	index = search_var(envlist, var);
	if (index > 0)
	{
		k = 0;
		while (envlist->vars[index][k] && envlist->vars[index][k] != '=')
			k++;
		return (ft_strdup(envlist->vars[index] + k + 1));
	}
	else
		return (NULL);
}

void	check_homepath(t_envlist *envlist, t_cmd_list *cmd)
{
	char	*tmp;
	char	*tmp0;

	if (!cmd->args[1] || !ft_strcmp(cmd->args[1], "~"))
	{
		free(cmd->args[1]);
		cmd->args[1] = get_env_val(envlist, "HOME");
	}
	if (!ft_strncmp(cmd->args[1], "~/", 2))
	{
		tmp = get_env_val(envlist, "HOME");
		tmp0 = ft_strjoin(tmp, cmd->args[1] + 1);
		free(cmd->args[1]);
		cmd->args[1] = tmp0;
		free(tmp);
	}
}

int	get_path(t_envlist *envlist, t_cmd_list *cmd)
{
	char	*tmp;

	check_homepath(envlist, cmd);
	if (!ft_strcmp(cmd->args[1], "-"))
	{
		tmp = get_env_val(envlist, "OLDPWD");
		if (!tmp)
		{
			printf("minishell: cd: OLDPWD not set\n");
			return (1);
		}
		free(cmd->args[1]);
		cmd->args[1] = tmp;
	}
	if (!ft_strcmp(cmd->args[1], ".."))
	{
		tmp = ft_strjoin(cmd->args[1], "/");
		free(cmd->args[1]);
		cmd->args[1] =tmp;
	}
	return (0);
}

int	builtin_cd(t_envlist *envlist, t_cmd_list *cmd)
{
	char	*tmp;
	char	*tmp0;
	int		index;

	if (get_path(envlist, cmd))
		return (1);
	if (chdir(cmd->args[1]) < 0)
	{
		printf("minishell: cd: %s: No such file or directory\n", cmd->args[1]);
		return (1);
	}
	index = search_var(envlist, "PWD");
	tmp = ft_strjoin("OLD", envlist->vars[index]);
	free(envlist->vars[index]);
	envlist->vars[index] = tmp;
	tmp0 = getcwd(NULL, MAXPATHLEN);
	free(tmp0);
	tmp = ft_strjoin("PWD=", tmp0);
	addto_envlist(envlist, tmp);
	free(tmp);
	return (0);
}


// int			exit_builtin(t_shell *shell, t_cmds *cmds)
// {
// 	long	status;
// 	int		i;
// 	int		is_cmd;

// 	if (!check_len(cmds))
// 		return (1);
// 	status = 0;
// 	is_cmd = cmds && cmds->start ? 1 : 0;
// 	i = -1;
// 	if (cmds && cmds->args[1])
// 		status = valid_status(cmds->args[1]);
// 	(is_cmd || !cmds) ? ft_del(shell->line) : 0;
// 	(is_cmd || !cmds) ? ft_free_arr(shell->env) : 0;
// 	(is_cmd || !cmds) ? ft_putstr_fd("exit\n", 2) : 0;
// 	(status > 200 && status < 300) ? print_error("exit", 33, 0) : 0;
// 	(is_cmd) ? free_shell(shell) : 0;
// 	(is_cmd || !cmds) ? ft_del(shell) : 0;
// 	exit(status);
// 	return (0);
// }
