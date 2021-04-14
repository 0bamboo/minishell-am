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

int is_valid_id(char *id)
{
	int   i;

	if (!ft_isalpha(id[0]))
    	return (1);
	i = 1;
	while (id[i])
	{
		if (!ft_isalpha(id[i]) && !ft_isalnum(id[i]) && id[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int is_valid_id0(char *id)
{
	int   i;

	if (!ft_isalpha(id[0]))
    	return (1);
	i = 1;
	while (id[i] && id[i] != '=')
	{
		if (!ft_isalpha(id[i]) && !ft_isalnum(id[i]) && id[i] != '_')
			return (1);
		i++;
	}
	return (0);
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

int	is_equalkey(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i])
		return (0);
	return (1);
}

int			search_var(t_envlist *envlist, char *var)
{
  char		*tmp;
  int		i;

  i = 0;
  tmp = ft_strjoin(var, "=");
  while (envlist->vars[i])
  {
    if (!ft_strcmp(envlist->vars[i], var)
		|| !ft_strncmp(envlist->vars[i], tmp, ft_strlen(tmp)))
	{
		free(tmp);
        return (i);
	}
    i++;
  }
  return (-1);
}

int			insert_var(t_envlist *envlist, char *var)
{
	char	*tmp;
	int		i;

	if (!is_equalkey(var))
    {
        tmp = ft_strdup(var);
        i = 0;
        while (tmp[i] != '=')
          i++;
        tmp[i] = 0;
        if (rmfrom_envlist(envlist, tmp))
			return (1);
        if (addto_envlist(envlist, var))
			return (1);
		free(tmp);
    }
    else
    {
        if (search_var(envlist, var) < 0)
        	if (addto_envlist(envlist, var))
				return (1);
	}
	return (0);
}