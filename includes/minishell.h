/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 18:05:05 by abdait-m          #+#    #+#             */
/*   Updated: 2021/03/19 18:19:46 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL
#define MINISHELL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../srcs/get_next_line.h"

typedef struct      o_parse
{
    char **sc_cmds;
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
char				**ft_split(s_split *sp, char const *s, char c);
char			*ft_itoa(int n);
// char			**ft_split(char const *s, char c);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_strchr(const char *s, int c);
char			*ft_strdup(const char *s);
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
int				ft_strlen(const char *s);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnstr(const char *str, const char *to_find, size_t len);
char			*ft_strrchr(const char *s, int c);

#endif