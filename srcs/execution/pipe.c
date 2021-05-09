#include "../../includes/minishell.h"

int	fork_subprocess(t_cmd_list *command, t_envlist *envlist)
{
	pid_t			pid;
	char			*path;

	pid = fork();
	if (pid < 0)
	{
		printf("%s\n", strerror(errno));
		return (1);
	}
	else if (!pid)
	{
		path = get_home_path(command->args, envlist->vars);
		if (command->iterator && command->nbrpipe && path)
		{	
			if (dup2(envlist->fds[command->iterator * 2 - 2], 0) < 0)
				perror("dup");
		}
		if (command->next && command->redir < 0 && path)
		{
			if (dup2(envlist->fds[command->iterator * 2 + 1], 1) < 0)
				perror("dup2");	
		}
		if (handle_redirection(command))
			exit (1);
		if (isbuiltin(command))
			exit(call_builtin(command, envlist));
		else if (execve(path, command->args, envlist->envp) < 0)
		{
			printf("minishell: %s: command not found\n", command->args[0]);
			exit(127);
		}
	}
	else
	{
		if (command->iterator && command->nbrpipe)
			close(envlist->fds[command->iterator * 2 - 2]);
		if (command->next)
			close(envlist->fds[command->iterator * 2 + 1]);
		envlist->pids[command->iterator] = pid;
	}
	return (pid);
}

int	implement_cmd(t_cmd_list *cmd, t_envlist *envlist, int nbr_pipe)
{
	if (cmd->args[0])
	{
		if (isbuiltin(cmd) && nbr_pipe == 0)
		{
			if (!handle_redirection(cmd))
				return(call_builtin(cmd, envlist));
			else
				return (1);
		}
		else
			return (fork_subprocess(cmd, envlist));
	}
	return (0);
}

void	save_fd(t_envlist *envlist)
{
	envlist->fd = malloc(sizeof(int) * 3);
	envlist->fd[0] = dup(0);
	envlist->fd[1] = dup(1);
	envlist->fd[2] = dup(2);
}

void	restore_fd(t_envlist *envlist)
{
	dup2(envlist->fd[0], 0);
	dup2(envlist->fd[1], 1);
	dup2(envlist->fd[2], 2);
}

int	execute_cmd(t_cmd_list *cmd, t_envlist *envlist)
{
	int		nbr_pipes;
	int		ret;
	int		status;
	t_cmd_list *tmp = cmd;
	int		i;
	
	
	nbr_pipes = cmd->nbrpipe;
	if (!g_ret)
		g_ret = 2;
	envlist->pids = malloc(sizeof(int) * (nbr_pipes + 1));
	if (nbr_pipes)
		envlist->fds = malloc(sizeof(int) * (nbr_pipes * 2));
	while (cmd)
	{
		if (cmd->next)
			pipe(envlist->fds + cmd->iterator * 2);
		ret = implement_cmd(cmd, envlist, nbr_pipes);
		cmd = cmd->next;
	}
	i = 0;
	status = 0;
	if (nbr_pipes)
	{
		while (i < nbr_pipes + 1)
			waitpid(envlist->pids[i++], &status, 0);
		free(envlist->pids);
		if (WIFEXITED(status))
			ret = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
    	    ret = status + 128;
	}
	else if (!isbuiltin(tmp))
	{
		waitpid(envlist->pids[0], &status, 0);
		free(envlist->pids);
		if (WIFEXITED(status))
			ret = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
    	    ret = status + 128;
	}
	clean_cmdList(cmd);
	return (ret);
}
