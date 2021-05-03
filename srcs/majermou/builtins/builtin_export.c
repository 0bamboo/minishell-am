#include "../minishell.h"

int	is_valid_id0(char *id)
{
	int		i;

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

void	printing(char **arr)
{
	int		i;
	int		j;

	i = 0;
	while (arr[i])
	{
		printf("declare -x ");
		j = 0;
		while (arr[i][j] && arr[i][j] != '=')
		{
			printf("%c", arr[i][j]);
			j++;
		}
		if (arr[i][j])
		{
			printf("=\"");
			printf("%s", arr[i] + ++j);
			printf("\"");
		}
		printf("\n");
		i++;
	}
}

int	print_envlist(t_envlist *envlist)
{
	char	**arr;
	int		i;

	arr = malloc((array_lenght(envlist->vars) + 1) * sizeof(char *));
	if (!arr)
		return (1);
	i = 0;
	while (envlist->vars[i])
	{
		str_copying(arr, envlist->vars[i], i);
		i++;
	}
	arr[i] = NULL;
	sorting(arr);
	printing(arr);
	cleanup(arr, array_lenght(arr));
	free(arr);
	return (0);
}

int	insert_var(t_envlist *envlist, char *var)
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

int	builtin_export(t_cmd_list *cmd, t_envlist *envlist)
{
	int		i;
	int		ret;
	char	*tmp;
	int		j;

	i = 1;
	ret = 0;
	while (cmd->args[i])
	{
		if (!is_valid_id0(cmd->args[i]))
			insert_var(envlist, cmd->args[i]);
		else
		{
			printf("minishell: export: `%s': not a valid identifier\n",
				cmd->args[i]);
			ret = 1;
		}
		i++;
	}
	if (i == 1)
		print_envlist(envlist);
	return (ret);
}
