#include "./includes/minishell.h"

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

void    signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_putstrs("\n");
		//ft_putstrs("\033[31m-> \033[35mminishell$> \033[0m");
	}
	else if (signal == SIGQUIT)
	{
		ft_putstrs("Quit: 3\n");
		return ;
	}
    // if (signal == SIGINT)
	// {
	// 	g_ret = 1;
	// }
    // else if (signal == SIGQUIT)
	// {
    //     write(1, "Quit: 3\n", 8);
	// }
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
	tmp[0] = ft_strdup(envlist->line);
	i = 1;
	j = 0;
	while (envlist->history && envlist->history[j])
		tmp[i++] = ft_strdup(envlist->history[j++]);
	tmp[i] = NULL;
	i = 0;
	while (envlist->history && envlist->history[i])
		free(envlist->history[i++]);
	free(envlist->history);
	envlist->history = tmp;
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	t_envlist	envlist;
	t_mp		*prs;

	(void)argv;
	(void)argc;
	g_ret = 0;
	prs = malloc(sizeof(t_mp));
	prs->sp = malloc(sizeof(t_sp));
	prs->cmds = NULL;
    prs->er = 0;
    prs->i = 0;
    prs->buff = NULL;
    prs->env = NULL;
    prs->temp = NULL;
    prs->global = NULL;
	envlist.history = NULL;
	envlist.status = 0;
	envlist.line = NULL;
	envlist.envp = envp;
	env_varsdup(&envlist,envp);
	rmfrom_envlist(&envlist, "OLDPWD");
	signal(SIGINT, signal_handler);
    signal(SIGQUIT, signal_handler);
	while (!ft_readline(&envlist))
	{
		ft_putstrs("\n");
		if (!g_ret && envlist.line && ft_strcmp(envlist.line, ""))
		{
			addTohistory(&envlist);
			_start_parsing(envlist.line, prs, &envlist);
			//free(envlist.line);
        }
        envlist.line = NULL;
    }
    return (0);
}