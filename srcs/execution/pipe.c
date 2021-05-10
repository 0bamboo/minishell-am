/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majermou <majermou@students.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 13:12:28 by majermou          #+#    #+#             */
/*   Updated: 2021/05/10 13:12:30 by majermou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_childProcess(t_cmd_list *cmd, t_envlist *envlist)
{
	char			*path;

	path = get_home_path(cmd->args, envlist->vars);
	if (cmd->iterator && cmd->nbrpipe && path)
		dup2(envlist->fds[cmd->iterator * 2 - 2], 0);
	if (cmd->next && cmd->redir < 0 && path)
		dup2(envlist->fds[cmd->iterator * 2 + 1], 1);
	if (handle_redirection(cmd))
		exit (1);
	if (isbuiltin(cmd))
	{
		free(path);
		exit(call_builtin(cmd, envlist));
	}
	if (execve(path, cmd->args, envlist->envp) < 0)
	{
		printf("minishell: %s: command not found\n", cmd->args[0]);
		exit(127);
	}
}

int	fork_subprocess(t_cmd_list *command, t_envlist *envlist)
{
	pid_t			pid;

	pid = fork();
	if (pid < 0)
	{
		printf("%s\n", strerror(errno));
		return (1);
	}
	else if (!pid)
		exec_childProcess(command, envlist);
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
				return (call_builtin(cmd, envlist));
			else
				return (1);
		}
		else
			return (fork_subprocess(cmd, envlist));
	}
	return (0);
}

int	wait_processes(t_envlist *envlist, int nbr_pipes, int is_builtin)
{
	int		status;
	int		ret;
	int		i;

	i = 0;
	status = 0;
	ret = 0;
	if (nbr_pipes)
	{
		while (i < nbr_pipes + 1)
			waitpid(envlist->pids[i++], &status, 0);
		free(envlist->fds);
	}
	else if (!is_builtin)
		waitpid(envlist->pids[0], &status, 0);
	free(envlist->pids);
	if (WIFEXITED(status))
		ret = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		ret = status + 128;
	return (ret);
}

int	execute_cmd(t_cmd_list *cmd, t_envlist *envlist)
{
	int		nbr_pipes;
	int		is_builtin;
	int		ret;

	envlist->head = cmd;
	nbr_pipes = cmd->nbrpipe;
	is_builtin = isbuiltin(cmd);
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
	ret = wait_processes(envlist, nbr_pipes, is_builtin);
	clean_cmdList(envlist);
	return (ret);
}
