/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 18:05:05 by abdait-m          #+#    #+#             */
/*   Updated: 2021/04/14 22:35:31 by abdait-m         ###   ########.fr       */
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
	int					nbrpipe;
	int					iter;
    int					end;
    int                 beg;
	struct  s_cmd_list	*next;
	struct  s_cmd_list	*prev;
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


typedef struct r_split
{
    char **p;
    int size;
    int i;
    int j;
    int idx;
    int check_dq;
    int check_sq;
}               s_split;



typedef struct      e_parse
{
    char **sc_cmds;
    char **sp_cmds;
    int er;
    int i;
    int j;
    int credir;
    char tmp;
    char *buff;
    char *token;
    char *buffer;
    char *fill;
    char *temp;
    int count;
    int counter;
    char *global;
    int g;
    err_p   err;
    t_cmd_list      *plst;
    s_split         *sp;
}                   ms_p;


void _start_parsing(char *line, ms_p *prs, t_cmd_list **head);
char				**_split_tokens(s_split *sp, char const *s, char c);
void        _trim_tokens(char **sp);
char *_get_env_vars_(char *buffer, ms_p *prs);
int _handle_syntax_errors(char *line, ms_p *prs);
void        _raise_an_exception();
int     _char_in_tab_(char c, char tab[3]);
char *_handle_backslash_(ms_p *prs, char *token);


#endif
