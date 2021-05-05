#include "../../includes/minishell.h"

int	fork_subprocess(t_cmd_list *command, t_envlist *envlist, int ***fds)
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
	else if (!pid)
	{
		path = get_home_path(command->args, envlist->envp);
		if (command->iterator && command->nbrpipe)
			if (dup2(fds[0][0][command->iterator * 2 - 2], 0) < 0)
				perror("dup");
		if (command->next && command->redir < 0)
			if (dup2(fds[0][0][command->iterator * 2 + 1], 1) < 0)
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
			close(fds[0][0][command->iterator * 2 - 2]);
		if (command->next)
			close(fds[0][0][command->iterator * 2 + 1]);
		if (command->nbrpipe) 
			fds[0][1][i++] = pid;
	}
	return (0);
}

int	fdsAllocation(int ***fds, int nbr_pipe)
{
	fds[0] = malloc(2 * sizeof(int *));
	if (nbr_pipe)
	{
		fds[0][0] = malloc(2 * nbr_pipe * sizeof(int));
		if (!fds[0][0])
			return (1);
		fds[0][1] = malloc((nbr_pipe + 1) * sizeof(int));
		if (!fds[0][1])
		{
			free(fds[0][0]);
			return (1);
		}
	}
	else
	{
		fds[0][1] = malloc(1 * sizeof(int));
		if (!fds[0][1])
			return (1);
	}
	return (0);
}

int	execute_cmd(t_cmd_list *cmd, t_envlist *envlist)
{
	int		**fds;
	int		nbr_pipes;
	int		ret;
	int		i;
	int		status;

	nbr_pipes = cmd->nbrpipe;
	if (fdsAllocation(&fds, nbr_pipes))
		return (1);
	while (cmd)
	{
		if (cmd->next)
			pipe(fds[0] + cmd->iterator * 2);
		ret = fork_subprocess(cmd, envlist, &fds);
		cmd = cmd->next;
	}
	i = 0;
	status = 0;
	if (nbr_pipes)
	{
		while (i < nbr_pipes + 1)
			waitpid(fds[1][i++], &status, 0);
		free(fds[0]);
		free(fds[1]);
		if (WIFEXITED(status))
			ret = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
    	    ret = status + 128;
	}
	else
	{
		waitpid(fds[1][0], &status, 0);
		free(fds[1]);
		if (WIFEXITED(status))
			ret = WEXITSTATUS(status);
	}
	return (ret);
}
