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
