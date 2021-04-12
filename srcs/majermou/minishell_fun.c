#include "minishell.h"

void	cleanup(char **arr, int limit)
{
	int		i;

	i = 0;
	while (i < limit)
	{
		free(arr[i]);
		i++;
	}
}

int	array_lenght(char **arr)
{
	int		lenght;

	lenght = 0;
	while (arr[lenght])
		lenght++;
	return (lenght);
}

unsigned int	random_num_generator(int range)
{
	void			*allocation;
	unsigned int	random;

	allocation = malloc(1);
	if (!allocation)
		return (range / 3);
	random = (unsigned)allocation;
	free(allocation);
	return (random % range);
}

int	str_copying(char **dst, char *src, int index)
{
	dst[index] = (char *)malloc((ft_strlen(src) + 1) * sizeof(char));
	if (!dst[index])
	{
		cleanup(dst, index);
		return (1);
	}
	ft_strlcpy(dst[index], src, ft_strlen(src) + 1);
	return (0);
}

int	env_varsdup(t_cmd_list *cmd, char **envp)
{
	char	**ret;
	int		i;

	ret = (char **)malloc((array_lenght(envp) + 1) * sizeof(char *));
	if (!ret)
		return (1);
	i = 0;
	while (envp[i])
	{
		ret[i] = (char *)malloc((ft_strlen(envp[i]) + 1) * sizeof(char));
		if (!ret)
		{
			cleanup(ret, i);
			return (1);
		}
		ft_strlcpy(ret[i], envp[i], ft_strlen(envp[i]) + 1);
		i++;
	}
	ret[i] = NULL;
	cmd->env_vars = ret;
	return (0);
}
