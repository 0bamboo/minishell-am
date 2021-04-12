/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majermou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 13:46:55 by majermou          #+#    #+#             */
/*   Updated: 2021/04/11 13:47:01 by majermou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

typedef struct          s_cmd_list
{
    char                **env_vars;
    char	            **args;
    int		            nbrpipe;
    int                 iterator;
    struct s_cmd_list   *next;                                   
}                       t_cmd_list;

size_t                  ft_strlen(const char *s);
size_t                  ft_strlcpy(char *dst, const char *src, size_t size);
int                     ft_strncmp(const char *s1, const char *s2, size_t n);
char	                *ft_strjoin(char const *s1, char const *s2);
int                     ft_strcmp(const char *s1, const char *s2);



int             env_varsdup(t_cmd_list *cmd, char **envp);
void	        cleanup(char **arr, int limit);
int             array_lenght(char **arr);
unsigned int	random_num_generator(int range);
int             str_copying(char **dst, char *src, int index);
int             rmfrom_envlist(t_cmd_list *cmd, char* rm_var);
int             addto_envlist(t_cmd_list *cmd, char* new_var);


#endif