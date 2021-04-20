#include "./builtins/minishell.h"

int	call_builtin(t_cmd_list *cmd, t_envlist *envlist)
{
	int		status;
	int		ret;

	status = 0;
	if (!ft_strncmp(cmd->args[0], "echo", 5))
		ret = builtin_echo(cmd);
	if (!ft_strncmp(cmd->args[0], "cd", 3))
		ret = builtin_cd(envlist, cmd);
	if (!ft_strncmp(cmd->args[0], "pwd", 4))
		ret = builtin_pwd();
	if (!ft_strncmp(cmd->args[0], "export", 7))
		ret = builtin_export(cmd, envlist);
	if (!ft_strncmp(cmd->args[0], "unset", 6))
		ret = builtin_unset(cmd, envlist);
	if (!ft_strncmp(cmd->args[0], "env", 4))
		ret = builtin_env(envlist);
	if (!ft_strncmp(cmd->args[0], "exit", 5))
		ret = builtin_exit(cmd, status);
	return (ret);
}

int	is_redir(t_cmd_list *cmd)
{
	int		i;

	i = 0;
	while (cmd->args[i])
	{
		if (!ft_strcmp(cmd->args[i], "<")
			|| !ft_strcmp(cmd->args[i], ">")
			|| !ft_strcmp(cmd->args[i], ">>"))
			return (i);
		i++;
	}
	return (-1);
}

int	handle_input(char **redir)
{
	int		input;

	if (!ft_strcmp(redir[0], "<"))
	{
		input = open(redir[1], O_RDONLY, 0);
		if (input == -1)
		{
			printf("%s\n", strerror(errno));
			return (1);
		}
		dup2(input, 0);
		close(input);
	}
	return (0);
}

void	handle_output(char **redir)
{
	int		output;

	if (!ft_strcmp(redir[0], ">"))
	{
		output = open(redir[1], O_WRONLY | O_TRUNC
				| O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
		dup2(output, 1);
		close(output);
	}
	if (!ft_strcmp(redir[0], ">>"))
	{
		output = open(redir[1], O_WRONLY | O_APPEND
				| O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
		dup2(output, 1);
		close(output);
	}
}

int	handle_redirection(t_cmd_list *cmd)
{
	int		i;

	i = is_redir(cmd);
	while (i >= 0 && cmd->args[i])
	{
		if (handle_input(cmd->args + i))
			return (1);
		handle_output(cmd->args + i);
		cmd->args[i++] = NULL;
		cmd->args[i++] = NULL;
	}
	return (0);
}
