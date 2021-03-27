/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 18:05:05 by abdait-m          #+#    #+#             */
/*   Updated: 2021/03/24 16:44:35 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL
#define MINISHELL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../srcs/get_next_line.h"
#include "../libft/libft.h"


typedef struct          o_list
{
    char                redir;
    char                pipe;
    char                beg;
    char                end;
    char                is_err;
    char                *cmd;
    char                **args;
    struct  o_list      *next;
    struct  o_list      *prev;
    
       
}                       p_list;
typedef struct      o_parse
{
    char **sc_cmds;
    char ***space_cmd;
    int pipe[100];
    p_list      dll;
}                   sc_parse;

typedef struct r_split
{
    char **p;
    int size;
    int i;
    int j;
    int check_dq;
    int check_sq;
}               s_split;

typedef struct f_parse
{
    sc_parse sc_prs;
    s_split sp;
    
}               g_parse;

void start_parsing(char *line, sc_parse *prs);
char        *my_strtok(char *s, char *check);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char				**_split_tokens(s_split *sp, char const *s, char c);
void        _trim_tokens(char **sp);


#endif