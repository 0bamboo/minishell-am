#include "../../includes/minishell.h"

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

unsigned int	random_num_generator(int range)
{
	void			*allocation;
	unsigned int	*random;

	random = NULL;
	allocation = malloc(1);
	if (!allocation)
		return (range / 3);
	random = (unsigned int *)allocation;
	free(allocation);
	return (*random % range);
}

void	handle_numeric(t_cmd_list *cmd, t_envlist *envlist)
{
	printf("minishell: exit: %s: numeric argument required\n", cmd->args[1]);
	cleaning(cmd, envlist);
	exit(255);
}

void	sorting(char **arr)
{
	char		*tmp;
	int			i;
	int			j;

	i = 0;
	while (arr[i])
	{
		j = i + 1;
		while (arr[j])
		{
			if (ft_strcmp(arr[i], arr[j]) >= 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

int	addToline(t_envlist *envlist, char buff)
{
	char	*tmp;
	int		i;

	i = 0;
	while (envlist->line && envlist->line[i] != '\0')
		i++;
	tmp = malloc(i + 2);
	if (!tmp)
		return (1);
	i = 0;
	while (envlist->line && envlist->line[i] != '\0')
	{
		tmp[i] = envlist->line[i];
		i++;
	}
	if (envlist->line)
		free(envlist->line);
	tmp[i++] = buff;
	tmp[i] = '\0';
	envlist->line = tmp;
	return (0);
}
