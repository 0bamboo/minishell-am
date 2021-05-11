#include "../../includes/minishell.h"

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
	free(envlist->fd);
	envlist->fd = NULL;
}
