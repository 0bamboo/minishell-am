#include "minishell.h"

int	rmfrom_envlist(t_cmd_list *cmd, char *rm_var)
{
	char		**ret;
	char		*str;
	int			i;
	int			j;

	ret = (char **)malloc(((array_lenght(cmd->env_vars) + 1) * sizeof(char *)));
	if (!ret)
		return (1);
	i = 0;
	j = 0;
	str = ft_strjoin(rm_var, "=");
	while (cmd->env_vars[i])
	{
		if (ft_strcmp(cmd->env_vars[i], rm_var)
			&& ft_strncmp(cmd->env_vars[i], str, ft_strlen(str)))
			if (str_copying(ret, cmd->env_vars[i], j++))
				return (1);
		i++;
	}
	ret[j] = NULL;
	free(str);
	cleanup(cmd->env_vars, array_lenght(cmd->env_vars));
	free(cmd->env_vars);
	cmd->env_vars = ret;
	return (0);
}

int	addto_envlist(t_cmd_list *cmd, char *new_var)
{
	char		**ret;
	int			i;
	int			j;
	int			random;

	ret = (char **)malloc((array_lenght(cmd->env_vars) + 2) * sizeof(char *));
	if (!ret)
		return (1);
	i = 0;
	j = 0;
	random = random_num_generator(array_lenght(cmd->env_vars));
	while (i < random)
		if (str_copying(ret, cmd->env_vars[i++], j++))
			return (1);
	if (str_copying(ret, new_var, j++))
		return (1);
	while (cmd->env_vars[i])
		if (str_copying(ret, cmd->env_vars[i++], j++))
			return (1);
	ret[j] = NULL;
	cleanup(cmd->env_vars, array_lenght(cmd->env_vars));
	free(cmd->env_vars);
	cmd->env_vars = ret;
	return (0);
}
