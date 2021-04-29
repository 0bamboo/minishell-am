/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_syntax_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 11:54:49 by abdait-m          #+#    #+#             */
/*   Updated: 2021/04/22 23:58:00 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	_char_in_tab_(char c, char tab[3])
{
	if (c == tab[0] || c == tab[1] || c == tab[2])
		return (1);
	return (0);
}

int	_is_white_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\r' || c == '\n')
		return (1);
	return 0;
}

int	_check_semi_colon(char *line, t_mp *prs)
{
	prs->i++;
	if (line[0] == ';')
	{
		prs->er = 1;
		return (prs->i);
	}
	while (prs->i)
	{
		if (line[prs->i] == '|' || line[prs->i] == ';')
		{
			prs->er = 1;
			break ;
		}
		else if (_is_white_space(line[prs->i]))
			prs->i++;
		else
			break;
	}
	return(--prs->i);
}

int	_check_pipe(char *line, t_mp *prs)
{
	prs->i++;
	if (line[0] == '|' || !line[prs->i + 1])
	{
		prs->er = 1;
		return (prs->i);
	}
	while (line[prs->i])
	{
		if (_is_white_space(line[prs->i]))
			prs->i++;
		else if (line[prs->i] == '|' || line[prs->i] == ';' ||
			line[prs->i] == '>' || line[prs->i] == '<')
		{
			prs->er = 1;
			break ;
		}
		else
			break ;
	}
	return (--prs->i);
}

int	_check_redirection(char *line, t_mp *prs)
{
	prs->credir = 1;
	prs->i++;
	while (line[prs->i])
	{
		if (prs->tmp == '>' && line[prs->i] == '>')
		{
			prs->tmp = '>';
			prs->credir += 1;
			prs->i++;
		}
		else if (line[prs->i + 1] && prs->tmp == '>' &&
			_is_white_space(line[prs->i]) && line[prs->i + 1] == '>')
		{
			prs->er = 1;
			return (prs->i);
		}
		else if (_is_white_space(line[prs->i]))
			prs->i++;
		else if (line[prs->i] == ';' || line[prs->i] == '|' || (line[prs->i] == '<' && prs->tmp == '>') ||
			(prs->tmp == '<' && (line[prs->i] == '>' || line[prs->i] == '<')) ||
			prs->credir >= 3)
		{
			prs->er = 1;
			return (prs->i);
		}
		else
			break;
	}
	if (!line[prs->i])
		prs->er = 1;
	return (--prs->i);
}

int	_check_double_quotes(char *line, t_mp *prs)
{
	prs->i++;
	while (line[prs->i] != prs->tmp && line[prs->i])
	{
		if (line[prs->i] == '\\' && line[prs->i + 1] != '\0')
		{
			prs->i += 2;
			continue ;
		}
		prs->i++;
	}
	if (line[prs->i] != prs->tmp)
		prs->er = 1; 
	return prs->i;
}

int	_check_single_quotes(char *line, t_mp *prs)
{
	prs->i++;
	while (line[prs->i] != '\'' && line[prs->i])
		prs->i++;
	if (line[prs->i] != prs->tmp)
		prs->er = 1;
	return prs->i;
}

int	_handle_syntax_errors(char *line, t_mp *prs)
{
	prs->i = 0;
	prs->er = 0;
	while (line[prs->i])
	{
		prs->tmp = line[prs->i];
		if (line[prs->i] == ';')
			prs->i = _check_semi_colon(line, prs);
		else if (line[prs->i] == '|') 
			prs->i = _check_pipe(line, prs);
		else if ((line[prs->i] == '>' || line[prs->i] == '<'))
			prs->i = _check_redirection(line, prs);
		else if (prs->tmp == '"')
			prs->i = _check_double_quotes(line, prs);
		else if (prs->tmp == '\'')
			prs->i = _check_single_quotes(line, prs);
		if (prs->er)
			return (1);
		prs->i++;
	}
	return (0);
}

void	_raise_an_exception()
{
	write(1, "mini$hell: Syntax error .\n", 26);
}
