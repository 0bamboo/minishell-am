#include "./includes/minishell.h"

void    signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		if (g_ret != 2)
			ft_putstrs("\n\033[31m-> \033[35mminishell$> \033[0m");
		else
			ft_putstrs("\n");
		g_ret = 1;
	}
	if (signal == SIGQUIT)
	{
		if (g_ret == 2)
			ft_putstrs("Quit: 3\n");
	}
}

int main(int argc, char **argv, char **envp)
{
	t_envlist	envlist;
	t_mp		*prs;
	int			ret;

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
	while (1)
	{
		g_ret = 0;
		ret = ft_readline(&envlist);
		if (ret == 1)
			break ;
		if (g_ret != 1)
			ft_putstrs("\n");
		if (envlist.line && ft_strcmp(envlist.line, ""))
		{
			addTohistory(&envlist);
			// printf("line == |%s|\n", envlist.line);
			_start_parsing(envlist.line, prs, &envlist);
			// free(envlist.line);
        }
        envlist.line = NULL;
    }
	cleaning(NULL, &envlist);
	(void)argc;
	(void)argv;
    return (0);
}