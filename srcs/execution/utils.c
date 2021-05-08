#include "../../includes/minishell.h"

int	removeFromline(t_envlist *envlist)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = envlist->line;
	envlist->line = malloc(ft_strlen(envlist->line) * sizeof(char));
	while (tmp[i + 1])
	{
		envlist->line[i] = tmp[i];
		i++;
	}
	envlist->line[i] = '\0';
	free(tmp);
	return (0);
}

void	clean_cmdList(t_cmd_list *cmd)
{
	int			i;
	t_cmd_list	*tmp;

	i = 0;
	if (cmd)
	{
		if (cmd->args)
		{
			while (cmd->args && cmd->args[i])
				free(cmd->args[i++]);
			free(cmd->args);
		}
		while (cmd)
		{
			tmp = cmd;
			cmd = cmd->next;
			free(tmp);
		}
	}
}

void	cleaning(t_cmd_list *cmd, t_envlist *envlist)
{
	int		i;

	if (envlist->vars)
	{
		i = 0;
		while (envlist->vars[i])
			free(envlist->vars[i++]);
		free(envlist->vars);
	}
	if (envlist->history)
	{
		i = 0;
		while (envlist->history[i])
			free(envlist->history[i++]);
		free(envlist->history);
	}
	// if (envlist->line)
	// 	free(envlist->line); 
	clean_cmdList(cmd);
}

char	*get_home_path(char **args, char **envp)
{
	struct stat		buf;
	char			**arr;
	char			*tmp;
	char			*path;

	while (strncmp(*envp, "PATH=", 5))
		envp++;
	arr = ft_split(*envp + 5, ':');
	while (*arr)
	{
		path = ft_strjoin(*arr++, "/");
		tmp = path;
		path = ft_strjoin(path, *args);
		free(tmp);
		if (!stat(path, &buf))
		{
			while (*arr)
				free(*arr++);
			return (path);
		}
		free(path);
	}
	return (NULL);
}

int	addTohistory(t_envlist *envlist)
{
	char		**tmp;
	int			lenght;
	int			i;
	int			k;

	lenght = 0;
	tmp = envlist->history;
	while (tmp && tmp[lenght])
		lenght++;
	envlist->history = malloc((lenght + 2) * sizeof(char *));
	if (!envlist->history)
		return (1);
	envlist->history[0] = ft_strdup(envlist->line);
	i = 1;
	k = 0;
	while (tmp && tmp[k])
		envlist->history[i++] = ft_strdup(tmp[k++]);
	envlist->history[i] = NULL;
	k = 0;
	while (tmp && tmp[k])
		free(tmp[k++]);
	free(tmp);
	return (0);
}
