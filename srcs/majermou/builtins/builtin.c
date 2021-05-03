#include "../minishell.h"

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

int	get_val(char *str)
{
	long long	num;
	int			i;
	int			sign;

	num = 0;
	i = 0;
	sign = 1;
	if (str[i] == '-')
	{
		i++;
		sign = -1;
	}
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 58)
		{
			printf("minishell: exit: %s: numeric argument required\n", str);
			exit(255);
		}
		num = num * 10 + (str[i++] - '0');
	}
	num *= sign;
	if ((num > 0 && sign < 0) || (num < 0 && sign > 0))
	{
		printf("minishell: exit: %s: numeric argument required\n", str);
		exit(255);
	}
	return (num % 256);
}

int	builtin_exit(t_cmd_list *cmd, int status)
{
	int		ret;

	printf("exit\n");
	if (!cmd->args[1])
		exit(status);
	ret = get_val(cmd->args[1]);
	if (cmd->args[2])
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	exit(ret);
}
