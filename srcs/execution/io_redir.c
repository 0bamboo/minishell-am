#include "../../includes/minishell.h"

int	isbuiltin(t_cmd_list *command)
{
	if (!ft_strncmp(command->args[0], "echo", 5)
		|| !ft_strncmp(command->args[0], "cd", 3)
		|| !ft_strncmp(command->args[0], "pwd", 4)
		|| !ft_strncmp(command->args[0], "export", 7)
		|| !ft_strncmp(command->args[0], "unset", 6)
		|| !ft_strncmp(command->args[0], "env", 4)
		|| !ft_strncmp(command->args[0], "exit", 5))
		return (0);
	else
		return (1);
}

int	call_builtin(t_cmd_list *cmd, t_envlist *envlist)
{
	if (!ft_strncmp(cmd->args[0], "echo", 5))
		return (builtin_echo(cmd));
	if (!ft_strncmp(cmd->args[0], "cd", 3))
		return (builtin_cd(envlist, cmd));
	if (!ft_strncmp(cmd->args[0], "pwd", 4))
		return (builtin_pwd());
	if (!ft_strncmp(cmd->args[0], "export", 7))
		return (builtin_export(cmd, envlist));
	if (!ft_strncmp(cmd->args[0], "unset", 6))
		return (builtin_unset(cmd, envlist));
	if (!ft_strncmp(cmd->args[0], "env", 4))
		return (builtin_env(envlist));
	if (!ft_strncmp(cmd->args[0], "exit", 5))
		return (builtin_exit(cmd, envlist->status));
	return (0);
}

int	handle_input(char **rdr)
{
	int		input;

	input = open(rdr[1], O_RDONLY, 0);
	if (input == -1)
	{
		printf("%s\n", strerror(errno));
		return (1);
	}
	dup2(input, 0);
	close(input);
	return (0);
}

void	handle_output(char **rdr)
{
	int		output;

	if (!ft_strcmp(rdr[0], ">"))
	{
		output = open(rdr[1], O_WRONLY | O_TRUNC
				| O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
		dup2(output, 1);
		close(output);
	}
	if (!ft_strcmp(rdr[0], ">>"))
	{
		output = open(rdr[1], O_WRONLY | O_APPEND
				| O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
		dup2(output, 1);
		close(output);
	}
}

int	handle_redirection(t_cmd_list *cmd)
{
	while (cmd->redir >= 0 && cmd->args[cmd->redir])
	{
		if (!ft_strcmp(cmd->args[cmd->redir], "<"))
		{
			if (handle_input(cmd->args + cmd->redir))
				return (1);
		}
		else
			handle_output(cmd->args + cmd->redir);
		cmd->args[cmd->redir++] = NULL;
		cmd->args[cmd->redir++] = NULL;
	}
	return (0);
}