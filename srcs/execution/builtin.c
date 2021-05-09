#include "../../includes/minishell.h"

int	builtin_pwd(void)
{
	char	*buf;

	buf = malloc((MAXPATHLEN + 1) * sizeof(char));
	if (!buf)
		return (1);
	printf("%s\n", getcwd(buf, MAXPATHLEN));
	free(buf);
	return (0);
}

int	check_option(char *str)
{
	int		i;

	i = 0;
	if (str[i] != '-')
		return (1);
	while (str[++i])
	{
		if (str[i] != 'n')
			return (1);
	}
	return (0);
}

int	builtin_echo(t_cmd_list *cmd)
{
	int		i;
	int		line;

	i = 1;
	line = 0;
	while (cmd->args[i] && !check_option(cmd->args[i]))
	{
		line = 1;
		i++;
	}
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}
	if (!line)
		printf("\n");
	return (0);
}

int	get_val(t_cmd_list *cmd, t_envlist *envlist)
{
	long long	num;
	int			i;
	int			sign;

	num = 0;
	i = 0;
	sign = 1;
	if (cmd->args[1][i] == '-')
	{
		i++;
		sign = -1;
	}
	while (cmd->args[1][i])
	{
		if (cmd->args[1][i] < 48 || cmd->args[1][i] > 58)
			handle_numeric(cmd, envlist);
		num = num * 10 + (cmd->args[1][i++] - '0');
	}
	num *= sign;
	if ((num > 0 && sign < 0) || (num < 0 && sign > 0))
		handle_numeric(cmd, envlist);
	return (num % 256);
}

int	builtin_exit(t_cmd_list *cmd, t_envlist *envlist)
{
	int		ret;

	printf("exit\n");
	if (!cmd->args[1])
	{
		cleaning(cmd, envlist);
		exit(envlist->status);
	}
	ret = get_val(cmd, envlist);
	if (cmd->args[2])
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	cleaning(cmd, envlist);
	exit(ret);
}
