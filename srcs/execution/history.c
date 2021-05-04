#include "../../includes/minishell.h"

int	addToline(t_envlist *envlist, char buff)
{
	char	*tmp;
	int		i;

	i = 0;
	while (envlist->line && envlist->line[i] != '\0')
		i++;
	tmp = malloc(i + 2);
	if (!tmp)
		return (1);
	i = 0;
	while (envlist->line && envlist->line[i] != '\0')
	{
		tmp[i] = envlist->line[i];
		i++;
	}
	if (envlist->line)
		free(envlist->line);
	tmp[i++] = buff;
	tmp[i] = '\0';
	envlist->line = tmp;
	return (0);
}

int	removeFromline(t_envlist *envlist)
{
	int		i;

	i = 0;
	while (envlist->line[i + 1])
		i++;
	envlist->line[i] = '\0';
	return (0);
}

void	handle_arrawkeys(t_envlist *envlist, long buff, int *curs, int *index)
{
	if ((buff == ARRW_UP && envlist->history)
		|| (buff == ARRW_DOWN && envlist->history))
	{
		while (curs[0] > 0)
		{
			tputs(cursor_left, 1, ft_putchars);
			tputs(delete_character, 1, ft_putchars);
			curs[0]--;
		}
		if (buff == ARRW_UP && envlist->history[index[0] + 1])
			index[0]++;
		if (buff == ARRW_DOWN && index[0] > -1)
			index[0]--;
		if (index[0] != -1)
		{
			curs[0] = ft_putstrs(envlist->history[index[0]]);
			free(envlist->line);
			envlist->line = ft_strdup(envlist->history[index[0]]);
		}
		else
		{
			free(envlist->line);
			envlist->line = NULL;
		}
	}
}

int	handleKeys(t_envlist *envlist, long buff, int *curs, int *index)
{
	if (buff == ENTER)
		return (1);
	else if (buff == ARRW_UP || buff == ARRW_DOWN)
		handle_arrawkeys(envlist, buff, curs, index);
	else if (buff == BACK_SPACE)
	{
		if (curs[0] > 0)
		{
			tputs(cursor_left, 1, ft_putchars);
			tputs(delete_character, 1, ft_putchars);
			removeFromline(envlist);
			curs[0]--;
		}
	}
	else
	{
		curs[0]++;
		addToline(envlist, buff);
		write(1, &buff, 1);
	}
	return (0);
}

int	readline(t_envlist *envlist)
{
	struct termios		p_term;
	long				buff;
	int					curs;
	int					index;

	buff = 0;
	curs = 0;
	index = -1;
	tgetent(NULL, getenv("TERM"));
	tcgetattr(0, &p_term);
	p_term.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(0, TCSANOW, &p_term);
	if (envlist->status)
		ft_putstrs("\033[31m-> \033[35mminishell$>\033[0m");
	else
		ft_putstrs("\033[32m-> \033[35mminishell$>\033[0m");
	while (read(0, &buff, sizeof(buff)))
	{
		if (handleKeys(envlist, buff, &curs, &index))
			break ;
		buff = 0;
	}
	p_term.c_lflag |= (ECHO | ICANON);
	tcsetattr(0, TCSANOW, &p_term);
	return (0);
}
