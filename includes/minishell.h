/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 18:05:05 by abdait-m          #+#    #+#             */
/*   Updated: 2021/03/29 16:52:59 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL
#define MINISHELL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../srcs/get_next_line.h"
#include "../libft/libft.h"


typedef struct			s_cmd_list
{
	char				*command;
	char				**args;
	char				redir;
	char				*file_id;
	int					pipe;
	int					beg;
    int					end;
    //char                is_err;
	struct  s_cmd_list		*next;
	struct  s_cmd_list		*prev;
}						t_cmd_list;

typedef struct errors
{
    int     dq;
    int     sq;
    int     countdq;
    int     countsq;
    int     i;
    char    tmp;
    int     len;
}               err_p;

typedef struct      e_parse
{
    char **sc_cmds;
    int pipe[100];
    char **sp_cmds;
    err_p   err;
    t_cmd_list      *plst;
}                   ms_p;

typedef struct r_split
{
    char **p;
    int size;
    int i;
    int j;
    int check_dq;
    int check_sq;
}               s_split;


void _start_parsing(char *line, ms_p *prs, t_cmd_list **head);
char        *my_strtok(char *s, char *check);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char				**_split_tokens(s_split *sp, char const *s, char c);
void        _trim_tokens(char **sp);


#endif
