#include "./builtins/minishell.h"

int	isbuiltin(t_cmd_list *command)
{
	if (!ft_strncmp(command->args[0], "echo", 5))
		return (0);
	if (!ft_strncmp(command->args[0], "cd", 3))
		return (0);
	if (!ft_strncmp(command->args[0], "pwd", 4))
		return (0);
	if (!ft_strncmp(command->args[0], "export", 7))
		return (0);
	if (!ft_strncmp(command->args[0], "unset", 6))
		return (0);
	if (!ft_strncmp(command->args[0], "env", 4))
		return (0);
	if (!ft_strncmp(command->args[0], "exit", 5))
		return (0);
	return (1);
}

char	*get_home_path(char **args, char **envp)
{
	struct stat		buf;
	char			**arr;
	char			*tmp;
	char			*path;
	int				i;

	i = 0;
	while (strncmp(envp[i], "PATH=", 5))
		i++;
	arr = ft_split(envp[i] + 5, ':');
	i = 0;
	while (arr[i])
	{
		path = ft_strjoin(arr[i++], "/");
		tmp = path;
		path = ft_strjoin(path, args[0]);
		free(tmp);
		if (!stat(path, &buf))
		{
			i = 0;
			while (arr[i])
				free(arr[i++]);
			return (path);
		}
		free(path);
	}
	return (NULL);
}
