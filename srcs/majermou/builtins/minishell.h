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

#include <sys/param.h>
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
    char	            **args;
    int		            nbrpipe;
    int                 iterator;
    struct s_cmd_list   *next;
}                       t_cmd_list;

typedef struct          s_envlist
{
    char	            **vars;
    char                *path;
}                       t_envlist;


size_t                  ft_strlen(const char *s);
size_t                  ft_strlcpy(char *dst, const char *src, size_t size);
int                     ft_strncmp(const char *s1, const char *s2, size_t n);
char	                *ft_strjoin(char const *s1, char const *s2);
int                     ft_strcmp(const char *s1, const char *s2);



void	        cleanup(char **arr, int limit);
int             array_lenght(char **arr);
unsigned int	random_num_generator(int range);
int             str_copying(char **dst, char *src, int index);
int             ft_isalpha(int c);
int             ft_isalnum(int c);
int             is_valid_id(char *id);
int             is_equalkey(char *str);

// int             rmfrom_envlist(t_cmd_list *cmd, char* rm_var);
// int             addto_envlist(t_cmd_list *cmd, char* new_var);
// int             env_varsdup(char **env_vars, char **envp);
// int             builtin_unset(t_cmd_list *cmd);
// int             builtin_export(t_cmd_list *cmd);
// int             builtin_env(t_cmd_list *cmd);
// int             search_var(t_cmd_list *cmd, char *var);
// int             replace_var(t_cmd_list *cmd,int index,char *new_var);

int			search_var(t_envlist *envlist, char *var);
int	        replace_var(t_envlist *envlist,int index,char *new_var);
int	        addto_envlist(t_envlist *envlist, char *new_var);
int	        rmfrom_envlist(t_envlist *envlist, char *rm_var);
int	        env_varsdup(t_envlist *envlist, char **envp);
int         builtin_unset(t_cmd_list *cmd, t_envlist *envlist);
int         builtin_export(t_cmd_list *cmd, t_envlist *envlist);
int         builtin_env(t_envlist *envlist);

int             builtin_pwd(void);
int             builtin_cd(t_envlist *envlist, t_cmd_list *cmd);
char            **ft_split(char const *s, char c);
int             is_valid_id0(char *id);
int			    insert_var(t_envlist *envlist, char *var);

char	*ft_strdup(const char *s);
int         print_envlist(t_envlist *envlist);
void  printing(char **arr);
void          sorting(char **arr);

int  get_path(t_envlist *envlist, t_cmd_list *cmd);
int	check_homepath(t_envlist *envlist, t_cmd_list *cmd);

int   builtin_exit(t_cmd_list *cmd, int status);
int builtin_echo(t_cmd_list *cmd);

#endif