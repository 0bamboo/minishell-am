/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 18:05:05 by abdait-m          #+#    #+#             */
/*   Updated: 2021/04/23 00:49:48 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL
#define MINISHELL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "../srcs/get_next_line.h"
#include "../libft/libft.h"
#define BUFFER_SIZE 1



typedef struct			s_cmd_list
{
	char				*command;
	char				**args;
	int					nbrpipe;
	int					iter;
    int                 redir;
	struct  s_cmd_list	*next;
}						t_cmd_list;

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
    // char **sp_cmds;
    int er;
    int i;
    int j;
    int g;
    int credir;
    int count;
    int counter;
    int status;
    int size;
    int nbrpipe;
    int len;
    char **pipe;
    char **cmds;
    char **files;
    char **args;
    char **array;
    char *buffer;//useable
    char *env;
    char *temp;//useable
    char *global;
    char tmp;
    // t_err   err;
    t_cmd_list      *head;
    t_sp         *sp;
}                   t_mp;
int     _is_white_space(char c);
void _count_tokens_dq_(t_sp *sp);
int			_count_tokens(char delim, t_sp *sp);
int			_len_tokens(t_sp *sp, char delim);
void _len_tokens_dq_(t_sp *sp);
void _len_tokens_sq_(t_sp *sp);
size_t	len_if(char *s, int nl);
char	*ft_dup_free(char *src, char **to_free);
int		build_line(char **line, char **buff, char **buff_s, char step);
int     _check_for_special_chars_(char *buff);
int _count_token_length_(t_mp *prs);
int     _size_of_arg_(t_mp *prs, char *buffer, int i);
void _free_tab_(char **buffer);
void _fill_list_for_normal_args_(t_mp *prs, char **args, char **files);
void _copy_files_(t_mp *prs);
void        _fix_the_order_(t_mp *prs);
void    _copy_redirs_(t_mp *prs);
void _copy_args_with_dq_(t_mp *prs);
void _copy_args_with_sq_(t_mp *prs);
void _handle_normal_args_2_(t_mp *prs);
void _handle_normal_args_(t_mp *prs, char *tmp);
int     _if_pipe_(t_mp *prs, int index);
void _fill_first_node_(t_mp *prs, char **args, char **files);
void    _fill_list_for_pipe_args_(t_mp *prs, t_cmd_list **head, char **args, char **files);
void        _handle_pipe_args_(t_mp *prs);
void        _copy_tokens_data_(t_mp *prs, int index);
int		get_next_line(int fd, char **line);
int		build_line(char **line, char **buff, char **buff_s, char step);
void _start_parsing(char *line, t_mp *prs);
char				**_split_tokens(t_sp *sp, char *s, char c);
void        _trim_tokens(t_sp *sp);
char *_get_env_vars_(char *buffer, t_mp *prs);
int _handle_syntax_errors(char *line, t_mp *prs);
void        _raise_an_exception();
int     _char_in_tab_(char c, char tab[3]);
char *_handle_backslash_(t_mp *prs, char *token);



#endif
