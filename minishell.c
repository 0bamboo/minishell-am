/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majermou <majermou@students.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 13:10:06 by majermou          #+#    #+#             */
/*   Updated: 2021/05/10 13:28:23 by majermou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	_init_vars_(t_envlist *envlist, t_mp *prs, char **envp)
{
	env_varsdup(envlist,envp);
	shell_lvl(envlist);
	envlist->status = 0;
	envlist->history = NULL;
	envlist->line = NULL;
	envlist->envp = envp;
	envlist->head = NULL;
	envlist->prs = prs;
	prs->sp = malloc(sizeof(t_sp));
	prs->sp->str = NULL;
	prs->sp->tmp = NULL;
	prs->cmds = NULL;
	prs->pipe = NULL;
	prs->files = NULL;
	prs->args = NULL;
    prs->buff = NULL;
	prs->array = NULL;
    prs->env = NULL;
    prs->temp = NULL;
    prs->global = NULL;
    prs->er = 0;
	signal(SIGINT, signal_handler);
    signal(SIGQUIT, signal_handler);
}

int main(int argc, char **argv, char **envp)
{
	t_envlist	*envlist;
	t_mp		*prs;
	int			ret;

	envlist = malloc(sizeof(t_envlist));
	prs = malloc(sizeof(t_mp));
	_init_vars_(envlist, prs, envp);
	while (1)
	{
		g_ret = 0;
		ret = ft_readline(envlist);
		if (ret == 1)
			break ;
		if (g_ret != 1)
			ft_putstrs("\n");
		if (envlist->line && ft_strcmp(envlist->line, ""))
		{
			addTohistory(envlist);
			_start_parsing(envlist->line, prs, envlist);
        }
        envlist->line = NULL;
    }
	cleaning(envlist);
	(void)argc;
	(void)argv;
    return (0);
}
