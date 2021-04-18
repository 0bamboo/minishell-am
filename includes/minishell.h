/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 18:05:05 by abdait-m          #+#    #+#             */
/*   Updated: 2021/04/18 13:41:59 by abdait-m         ###   ########.fr       */
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
	struct  s_cmd_list	*next;
}						t_cmd_list;

// typedef struct s_err
// {
//     int     dq;
//     int     sq;
//     int     countdq;
//     int     countsq;
//     int     i;
//     char    tmp;
//     int     len;
// }               t_err;


typedef struct s_sp
{
    char **str;
    char *tmp;
    int start;
    int end;
    int size;
    int i;
    int j;
    int k;
    int idx;
    int count;
}               t_sp;



typedef struct      s_mp
{
    char **cmds;
    // char **sp_cmds;
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
    int status;
    char *global;
    int g;
    // t_err   err;
    t_cmd_list      *plst;
    t_sp         *sp;
}                   t_mp;

int		get_next_line(int fd, char **line);
int		build_line(char **line, char **buff, char **buff_s, char step);
void _start_parsing(char *line, t_mp *prs, t_cmd_list **head);
void				_split_tokens(t_mp *prs, t_sp *sp, char *s, char c);
void        _trim_tokens(t_mp *prs);
char *_get_env_vars_(char *buffer, t_mp *prs);
int _handle_syntax_errors(char *line, t_mp *prs);
void        _raise_an_exception();
int     _char_in_tab_(char c, char tab[3]);
char *_handle_backslash_(t_mp *prs, char *token);



#endif
