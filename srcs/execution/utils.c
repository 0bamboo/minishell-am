#include "../../includes/minishell.h"

// char	*get_home_path(char **args, char **envp)
// {
// 	struct stat		buf;
// 	char			**arr;
// 	char			*tmp;
// 	char			*path;

// 	while (strncmp(*envp, "PATH=", 5))
// 		envp++;
// 	arr = ft_split(*envp + 5, ':');
// 	while (*arr)
// 	{
// 		path = ft_strjoin(*arr++, "/");
// 		tmp = path;
// 		path = ft_strjoin(path, *args);
// 		free(tmp);
// 		if (!stat(path, &buf))
// 		{
// 			while (*arr)
// 				free(*arr++);
// 			return (path);
// 		}
// 		free(path);
// 	}
// 	return (NULL);
// }

char	*get_home_path(char **args, char **envp)
{
	struct stat		buf;
	char			**arr;
	char			*tmp;
	char			*path;
	int				i;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5))
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
