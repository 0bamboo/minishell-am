#include "./minishell.h"

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
