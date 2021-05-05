#include "../../includes/minishell.h"

int	allocation_free(int **fds, int **shut_pid, int nbr_pipes, int param)
{
	if (!param)
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
		else
		{
			shut_pid[0] = malloc(1 * sizeof(int));
			if (!shut_pid[0])
				return (1);
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

int	fork_subprocess(t_cmd_list *command, t_envlist *envlist, int *fds, int **shut_pid)
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
			if (dup2(fds[command->iterator * 2 - 2], 0) < 0)
				perror("dup");
		if (command->next && command->redir < 0)
			if (dup2(fds[command->iterator * 2 + 1], 1) < 0)
				perror("dup2");
		if (handle_redirection(command))
			exit (1);
		if (isbuiltin(command))
			call_builtin(command, envlist);
		else if (execve(path, command->args, envlist->envp) < 0)
			exit(127);
		exit(0);
	}
	else
	{
		if (command->iterator && command->nbrpipe)
			close(fds[command->iterator * 2 - 2]);
		if (command->next)
			close(fds[command->iterator * 2 + 1]);
		if (command->nbrpipe) 
			shut_pid[i++] = pid;
	}
	return (pid);
}

int	execute_cmd(t_cmd_list *cmd, t_envlist *envlist)
{
	int		*shut_pid;
	int		*fds;
	pid_t pid;
	int		nbr_pipes;
	int		ret = 0;
	int		i;
	int		status;

	i = 0;
	status = 0;
	nbr_pipes = cmd->nbrpipe;
	if (allocation_free(&fds, &shut_pid, nbr_pipes, 0))
		return (1);
	while (cmd)
	{
		if (cmd->next)
			pipe(fds + cmd->iterator * 2);
		ret = fork_subprocess(cmd, envlist, fds, shut_pid);
		pid = ret;
		cmd = cmd->next;
	}
	if (nbr_pipes)
	{
		while (i < nbr_pipes + 1)
			waitpid(shut_pid[i++], &status, 0);
		if (WIFEXITED(status))
			ret = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
    	    ret = status + 128;
		allocation_free(&fds, &shut_pid, nbr_pipes, 1);
	}
	else
	{
		waitpid(pid, &status, 0);
		// free(shut_pid);
		if (WIFEXITED(status))
			ret = WEXITSTATUS(status);
	}
	return (ret);
}
