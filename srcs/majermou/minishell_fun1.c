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

int search_equalkey(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

void	*search_var(t_cmd_list *cmd, char *var)
{
	int   i;

	i = 0;
	while (cmd->env_vars[i])
  	{
		if (!ft_strncmp(cmd->env_vars[i],var,search_equalkey(var) + 1)
			|| (!ft_strncmp(cmd->env_vars[i],var,search_equalkey(var))
			&& cmd->env_vars[i][search_equalkey(var)] == '='))
			return (i);
    	i++;
	}
	return (-1);
}

int	replace_var(t_cmd_list *cmd,int index,char *new_var)
{
	free(cmd->env_vars[index]);
	cmd->env_vars[index] = malloc((ft_strlen(new_var) + 1) * sizeof(char *));
	if (!cmd->env_vars[index])
		return (1);
	ft_strlcpy(cmd->env_vars[index],new_var,ft_strlen(new_var));
	return (0);
}
