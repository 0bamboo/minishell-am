#include "./builtins/minishell.h"

int	fork_subprocess(t_cmd_list *command, t_envlist *envlist, int *fds, int *shut_pid)
{
	pid_t			pid;
	char			*path;
	static int		i;

	pid = fork();
	if (pid < 0)
	{
		printf("%s\n", strerror(errno));
		return (1);
	}
	if (!pid)
	{
		path = get_home_path(command->args, envlist->envp);
		if (command->iterator && command->nbrpipe)
			dup2(fds[command->iterator * 2 - 2], 0);
		if (command->next && is_redir(command) < 0)
			dup2(fds[command->iterator * 2 + 1], 1);
		if (handle_redirection(command))
			exit (1);
		if (execve(path, command->args, envlist->envp) < 0)
			exit(127);
	}
	else
	{
		if (command->iterator && command->nbrpipe)
			close(fds[command->iterator * 2 - 2]);
		if (command->next)
			close(fds[command->iterator * 2 + 1]);
		shut_pid[i++] = pid;
	}
	return (0);
}

int	allocation_free(int **fds, int **shut_pid, int nbr_pipes, int bool)
{
	if (!bool)
	{
		if (nbr_pipes)
		{
			fds[0] = malloc(2 * nbr_pipes * sizeof(int));
			if (!fds[0])
				return (1);
			shut_pid[0] = malloc((nbr_pipes + 1) * sizeof(int));
			if (!shut_pid[0])
			{
				free(fds[0]);
				return (1);
			}
		}
	}
	else
	{
		if (nbr_pipes)
		{
			free(shut_pid[0]);
			free(fds[0]);
		}
	}
	return (0);
}

int	implement_cmd(t_cmd_list *cmd, t_envlist *envlist, int *fds, int *shut_pid)
{
	if (!isbuiltin(cmd))
	{
		if (cmd->iterator && cmd->nbrpipe)
			dup2(fds[cmd->iterator * 2 - 2], 0);
		if (cmd->next && is_redir(cmd) < 0)
			dup2(fds[cmd->iterator * 2 + 1], 1);
		if (!handle_redirection(cmd))
			return (call_builtin(cmd, envlist));
		else
			return (1);
	}
	else
		return (fork_subprocess(cmd, envlist, fds, shut_pid));
}

int	execute_cmd(t_cmd_list *cmd, t_envlist *envlist)
{
	int		*shut_pid;
	int		*fds;
	int		nbr_pipes;
	int		ret;
	int		i;
	int		status;

	i = 0;
	nbr_pipes = cmd->nbrpipe;
	if (allocation_free(&fds, &shut_pid, nbr_pipes, 0))
		return (1);
	while (cmd)
	{
		if (cmd->next)
			pipe(fds + cmd->iterator * 2);
		ret = implement_cmd(cmd, envlist, fds, shut_pid);
		cmd = cmd->next;
	}
	while (i < nbr_pipes + 1)
		waitpid(shut_pid[i++], &status, 0);
	allocation_free(&fds, &shut_pid, nbr_pipes, 1);
	if (WIFEXITED(status))
		ret = WEXITSTATUS(status);
	return (ret);
}
