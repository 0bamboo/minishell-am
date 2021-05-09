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

void	handle_arrawkeys(t_envlist *envlist, long buff, int *lenght, int *index)
{
	if ((buff == ARROW_UP && envlist->history)
		|| (buff == ARROW_DOWN && envlist->history))
	{
		while (lenght[0] > 0)
		{
			tputs(cursor_left, 1, ft_putchars);
			tputs(delete_character, 1, ft_putchars);
			lenght[0]--;
		}
		if (buff == ARROW_UP && envlist->history[index[0] + 1])
			index[0]++;
		if (buff == ARROW_DOWN && index[0] > -1)
			index[0]--;
		if (index[0] != -1)
		{
			*lenght = ft_putstrs(envlist->history[index[0]]);
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

void	handle_backspace(t_envlist *envlist, int *lenght, int *bol,int param)
{
	if (param && *lenght > 0)
	{
		tputs(cursor_left, 1, ft_putchars);
		tputs(delete_character, 1, ft_putchars);
		removeFromline(envlist);
		lenght[0]--;
	}
	else if (!param)
	{
		free(envlist->line);
		envlist->line = ft_strdup("");
		*lenght = 0;
		*bol = 1;
	}
}

int	handleKeys(t_envlist *envlist, long buff, int *lenght, int *index)
{
	int		bol;

	bol = 0;
	while (read(0, &buff, sizeof(buff)))
	{
		if (g_ret == 1 && !bol)
			handle_backspace(envlist, lenght, &bol, 0);
		if (buff == ARROW_UP || buff == ARROW_DOWN)
			handle_arrawkeys(envlist, buff, lenght, index);
		else if (buff == BACK_SPACE)
			handle_backspace(envlist, lenght, &bol, 1);
		else if (buff == CTRL_D && !lenght[0])
		{
			ft_putstrs("exit\n");
			return (1);
		}
		else if (ft_isprint(buff))
		{
			lenght[0]++;
			addToline(envlist, buff);
			write(1, &buff, 1);
		}
		else if (buff == ENTER)
		{
			if (bol)
				ft_putstrs("\n");
			return (0);
		}
		buff = 0;
	}
	return (0);
}

int	ft_readline(t_envlist *envlist)
{
	struct termios		p_term;
	long				buff;
	int					lenght;
	int					index;
	int					ret;

	buff = 0;
	lenght = 0;
	index = -1;
	ret = 0;
	tgetent(NULL, getenv("TERM"));
	tcgetattr(0, &p_term);
	p_term.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(0, TCSANOW, &p_term);
	if (envlist->status)
		ft_putstrs("\033[31m-> \033[35mminishell$> \033[0m");
	else
		ft_putstrs("\033[32m-> \033[35mminishell$> \033[0m");
	ret = handleKeys(envlist, buff, &lenght, &index);
	p_term.c_lflag |= (ECHO | ICANON);
	tcsetattr(0, TCSANOW, &p_term);
	return (ret);
}
