#include "minishell.h"

int			search_var(t_envlist *envlist, char *var)
{
	int		i;

	i = 0;
	while (envlist->vars[i])
  	{
		if (!ft_strcmp(envlist->vars[i], var)
			|| (!ft_strncmp(envlist->vars[i], var,lenghtvar(var) + 1)))
			return (i);
    	i++;
	}
	return (-1);
}

int	replace_var(t_envlist *envlist,int index,char *new_var)
{
	free(envlist->vars[index]);
	envlist->vars[index] = malloc((ft_strlen(new_var) + 1) * sizeof(char *));
	if (!envlist->vars[index])
		return (1);
	ft_strlcpy(envlist->vars[index],new_var,ft_strlen(new_var) + 1);
	return (0);
}

int	addto_envlist(t_envlist *envlist, char *new_var)
{
	char		**ret;
	int			i;
	int			j;
	int			random;

	ret = (char **)malloc((array_lenght(envlist->vars) + 2) * sizeof(char *));
	if (!ret)
		return (1);
	i = 0;
	j = 0;
	random = random_num_generator(array_lenght(envlist->vars));
	while (i < random)
		if (str_copying(ret, envlist->vars[i++], j++))
			return (1);
	if (str_copying(ret, new_var, j++))
		return (1);
	while (envlist->vars[i])
		if (str_copying(ret, envlist->vars[i++], j++))
			return (1);
	ret[j] = NULL;
	cleanup(envlist->vars, array_lenght(envlist->vars));
	free(envlist->vars);
	envlist->vars = ret;
	return (0);
}

int	rmfrom_envlist(t_envlist *envlist, char *rm_var)
{
	char		**ret;
	char		*str;
	int			i;
	int			j;

	ret = (char **)malloc(((array_lenght(envlist->vars) + 1) * sizeof(char *)));
	if (!ret)
		return (1);
	i = 0;
	j = 0;
	str = ft_strjoin(rm_var, "=");
	while (envlist->vars[i])
	{
		if (ft_strcmp(envlist->vars[i], rm_var)
			&& ft_strncmp(envlist->vars[i], str, ft_strlen(str)))
			if (str_copying(ret, envlist->vars[i], j++))
				return (1);
		i++;
	}
	ret[j] = NULL;
	free(str);
	cleanup(envlist->vars, array_lenght(envlist->vars));
	free(envlist->vars);
	envlist->vars = ret;
	return (0);
}

int	env_varsdup(t_envlist *envlist, char **envp)
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
	envlist->vars = ret;
	return (0);
}