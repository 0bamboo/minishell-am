#include "./includes/minishell.h"



void    signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		g_ret = 1;
		//ft_putstrs("\n\033[31m-> \033[35mminishell$> \033[0m");
	}
	else if (signal == SIGQUIT)
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

	signal(SIGINT, signal_handler);
    signal(SIGQUIT, signal_handler);
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



	while (1)
	{
		g_ret = 0;
		ret = ft_readline(&envlist);
		if (ret)
			break;
		ft_putstrs("\n");
		if (envlist.line && ft_strcmp(envlist.line, ""))
		{
			addTohistory(&envlist);
			_start_parsing(envlist.line, prs, &envlist);
			//free(envlist.line);
        }
        envlist.line = NULL;
    }

	cleaning(NULL, &envlist);
	(void)argc;
	(void)argv;
    return (0);
}