/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_backslash_dq.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 11:58:13 by abdait-m          #+#    #+#             */
/*   Updated: 2021/05/09 21:54:13 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	_ret_special(char c)
{
	if (c == '\\')
		return ('\\');
	else if (c == '"')
		return ('"');
	else if (c == '$')
		return ('$');
	else
		return (0);
}

int	_bs_special(char c)
{
	if (c == '\\' || c == '"' || c == '$')
		return (1);
	return (0);
}

void	_bs_for_double_quotes_(t_mp *prs, char *token)
{
	prs->i++;
	while (token[prs->i] != '"')
	{
		if (token[prs->i] == '\\' && _bs_special(token[prs->i + 1]))
		{
			prs->buff[prs->j++] = _ret_special(token[prs->i + 1]);
			prs->i += 2;
			continue ;
		}
		prs->buff[prs->j++] = token[prs->i++];
	}
	prs->i++;
}

void	_bs_for_single_quotes_(t_mp *prs, char *token)
{
	prs->i++;
	while (token[prs->i] != '\'')
		prs->buff[prs->j++] = token[prs->i++];
	prs->i++;
}

char	*_handle_backslash_(t_mp *prs, char *token)
{
	int	len;

	len = ft_strlen(token);
	prs->i = 0;
	prs->j = 0;
	prs->buff = (char *)malloc(sizeof(char) * (len + 1));
	if (!prs->buff)
		return (NULL);
	while (prs->i < len)
	{
		if (token[prs->i] == '"')
			_bs_for_double_quotes_(prs, token);
		else if (token[prs->i] == '\'')
			_bs_for_single_quotes_(prs, token);
		else
			prs->buff[prs->j++] = token[prs->i++];
	}
	prs->buff[prs->j] = '\0';
	// free(token);
	return (prs->buff);
}
