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

void    sig_handle(int sig)
{
    if (sig == SIGINT)
        printf("%d\n", sig);
    else if (sig == SIGQUIT)
        printf("Quit: 3\n");
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
	t_mp *prs;
	int i = 0;
	
	(void)argv;
	(void)argc;
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
	// signal(SIGINT, sig_handle);
    // signal(SIGQUIT, sig_handle);
	
	while (!readline(&envlist))
	{
		printf("\n");
		if (envlist.line && ft_strcmp(envlist.line, ""))
		{
        	//printf("%s\n", envlist.line);
			addTohistory(&envlist);
			_start_parsing(envlist.line, prs, &envlist);
        }
        envlist.line = NULL;
    }


	// Cleaning --->
    i = 0;
    while (envlist.history && envlist.history[i])
    {
        free(envlist.history[i++]);
    }
	if (envlist.history)
    	free(envlist.history);
	i = 0;
	while (envlist.vars && envlist.vars[i])
    {
        free(envlist.vars[i++]);
    }
    free(envlist.vars);

    return (0);
}