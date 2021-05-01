#include "./builtins/minishell.h"

int	ft_putstrs(char *str)
{
	if (str)
	{
		write(1, str, ft_strlen(str));
		return (ft_strlen(str));
	}
	return (0);
}

int	ft_putchars(int c)
{
	write(0, &c, 1);
	return (0);
}

int	addTohistory(t_envlist *envlist)
{
	char		**tmp;
	int			i;
	int			j;

	i = 0;
	while (envlist->history && envlist->history[i])
		i++;
	tmp = malloc((i + 2) * sizeof(char *));
	if (!tmp)
		return (1);
	tmp[0] = envlist->line;
	i = 1;
	j = 0;
	while (envlist->history && envlist->history[j])
		tmp[i++] = envlist->history[j++];
	tmp[i] = NULL;
	free(envlist->history);
	envlist->history = tmp;
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	t_envlist   envlist;
	
	envlist.history = NULL;
	envlist.status = 0;
	envlist.line = NULL;
	int i = 0;
	while (!readline(&envlist))
	{
		printf("\n");
		if (envlist.line && ft_strcmp(envlist.line, ""))
		{
        	printf("%s\n", envlist.line);
        	addTohistory(&envlist);
        }
        envlist.line = NULL;
    }

    // i = 0;
    // while (envlist.history[i])
    // {
    //     free(envlist.history[i++]);
    // }
    // free(envlist.history);

    return (0);
}