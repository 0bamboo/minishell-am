/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majermou <majermou@students.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 18:05:05 by abdait-m          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/05/10 14:24:28 by majermou         ###   ########.fr       */
=======
/*   Updated: 2021/05/10 14:33:02 by abdait-m         ###   ########.fr       */
>>>>>>> e68aa33bc16aa51989b2f6aa6b682987045f6523
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "../libft/libft.h"
# include <sys/param.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <term.h>
# include <termios.h>
# include <curses.h>

# define ARROW_UP 4283163
# define ARROW_DOWN 4348699
# define BACK_SPACE 127
# define CTRL_D 4
# define ENTER 10
# define BUFFER_SIZE 1

int						g_ret;

typedef struct s_cmd_list
{
	char				**args;
	int					nbrpipe;
	int					iterator;
	int					redir;
	struct s_cmd_list	*next;
}						t_cmd_list;

typedef struct s_sp
{
	char				**str;
	char				*tmp;
	int					start;
	int					end;
	int					size;
	int					i;
	int					j;
	int					k;
	int					idx;
	int					count;
}						t_sp;

typedef struct s_mp
{
	t_cmd_list			*head;
	t_sp				*sp;
	char				**pipe;
	char				**cmds;
	char				**files;
	char				**args;
	char				**array;
	char				*buff;
	char				*env;
	char				*temp;
	char				*global;
	int					er;
	int					i;
	int					j;
	int					g;
	int					credir;
	int					count;
	int					counter;
	int					status;
	int					size;
	int					nbrpipe;
	int					len;
	int					iter;
	char				tmp;
}						t_mp;

typedef struct s_envlist
{
	t_cmd_list			*head;
	char				**vars;
	char				**envp;
	char				*line;
	char				**history;
	int					status;
	pid_t				*pids;
	int					*fds;
	int					*fd;
	t_mp				*prs;
}						t_envlist;

int						_is_white_space(char c);
void					_execute_(t_mp *prs, t_envlist *env);
void					_free_all_(t_mp *prs, t_sp *sp);
void					_env_var_counter_(t_mp *prs, t_envlist *env);
void					_env_var_copy_(t_mp *prs, t_envlist *env);
void					_size_of_arg_dq_(t_mp *prs);
void					_size_of_arg_sq_(t_mp *prs);
int						_check_semi_colon(char *line, t_mp *prs);
int						_check_pipe(char *line, t_mp *prs);
int						_check_single_quotes(char *line, t_mp *prs);
int						_line_counter_(t_mp *prs, t_envlist *env);
void					_count_inside_sq_(t_mp *prs);
void					_count_inside_dq_(t_mp *prs, t_envlist *env);
void					_count_command_status(t_mp *prs);
void					_count_dollar_digits_(t_mp *prs);
void					_copy_env_vars_(t_mp *prs, t_envlist *env);
void					_copy_dollar_digits_(t_mp *prs);
void					_count_env_vars_(t_mp *prs, t_envlist *env);
void					_push_back_string_(char *buff, int index, char *fill,
							int size);
int						_isspec_(char c);
void					_trim_tokens(t_sp *sp);
void					_add_to_string_(t_sp *sp, int size);
void					_sp_handle_single_quotes_(t_sp *sp);
void					_count_tokens_dq_(t_sp *sp);
int						_count_tokens(char delim, t_sp *sp);
int						_len_tokens(t_sp *sp, char delim);
void					_len_tokens_dq_(t_sp *sp);
void					_len_tokens_sq_(t_sp *sp);
int						_check_for_special_chars_(char *buff);
int						_count_token_length_(t_mp *prs);
int						_size_of_arg_(t_mp *prs, char *buffer, int i);
<<<<<<< HEAD
void					_free_tab_(char **buffer);
void					_fill_list_for_normal_args_(t_mp *prs, char **args,
							char **files);
=======
void					_free_tab_(t_mp *prs, char **buffer, int check);
void					_fill_list_for_normal_args_(t_mp *prs, char **args, char **files);
>>>>>>> e68aa33bc16aa51989b2f6aa6b682987045f6523
void					_copy_files_(t_mp *prs);
void					_fix_the_order_(t_mp *prs);
void					_copy_redirs_(t_mp *prs);
void					_copy_args_with_dq_(t_mp *prs);
void					_copy_args_with_sq_(t_mp *prs);
void					_handle_normal_args_2_(t_mp *prs);
void					_handle_normal_args_(t_mp *prs, char *tmp);
int						_if_pipe_(t_mp *prs, int index);
void					_fill_first_node_(t_mp *prs, char **args,
							char **files);
void					_fill_list_for_pipe_args_(t_mp *prs, t_cmd_list **head,
							char **args, char **files);
void					_handle_pipe_args_(t_mp *prs);
void					_copy_tokens_data_(t_mp *prs, int index);
void					_start_parsing(char *line, t_mp *prs, t_envlist *env);
char					**_split_tokens(t_sp *sp, char *s, char c);
void					_trim_tokens(t_sp *sp);
char					*_get_env_vars_(char *buffer, t_mp *prs,
							t_envlist *env);
int						_handle_syntax_errors(char *line, t_mp *prs);
void					_raise_an_exception(void);
int						_char_in_tab_(char c, char arr[3]);
char					*_handle_backslash_(t_mp *prs, char *token);
void					handle_numeric(t_cmd_list *cmd, t_envlist *envlist);
size_t					ft_strlen(const char *s);
size_t					ft_strlcpy(char *dst, const char *src, size_t size);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
char					*ft_strjoin(char const *s1, char const *s2);
int						ft_strcmp(const char *s1, const char *s2);
char					**ft_split(char const *s, char c);
void					cleanup(char **arr, int limit);
int						array_lenght(char **arr);
unsigned int			random_num_generator(int range);
int						str_copying(char **dst, char *src, int index);
int						ft_isalpha(int c);
int						ft_isalnum(int c);
int						is_valid_id(char *id);
int						is_equalkey(char *str);
int						search_var(t_envlist *envlist, char *var);
int						replace_var(t_envlist *envlist, int index,
							char *new_var);
int						addto_envlist(t_envlist *envlist, char *new_var);
int						rmfrom_envlist(t_envlist *envlist, char *rm_var);
int						env_varsdup(t_envlist *envlist, char **envp);
int						builtin_unset(t_cmd_list *cmd, t_envlist *envlist);
int						builtin_export(t_cmd_list *cmd, t_envlist *envlist);
int						builtin_env(t_envlist *envlist);
int						builtin_pwd(void);
int						builtin_cd(t_envlist *envlist, t_cmd_list *cmd);
char					**ft_split(char const *s, char c);
int						is_valid_id0(char *id);
int						insert_var(t_envlist *envlist, char *var);
char					*ft_strdup(const char *s);
int						print_envlist(t_envlist *envlist);
void					printing(char **arr);
void					sorting(char **arr);
int						check_homepath(t_envlist *envlist, t_cmd_list *cmd);
int						builtin_exit(t_cmd_list *cmd, t_envlist *envlist);
int						builtin_echo(t_cmd_list *cmd);
int						handle_redirection(t_cmd_list *command);
int						is_redir(t_cmd_list *cmd);
int						execute_cmd(t_cmd_list *cmd, t_envlist *envlist);
int						isbuiltin(t_cmd_list *command);
int						call_builtin(t_cmd_list *cmd, t_envlist *envlist);
char					*get_home_path(char **args, char **envp);
void					sig_handle(int sig);
void					restore_fd(t_envlist *envlist);
void					save_fd(t_envlist *envlist);
int						ft_putstrs(char *str);
int						ft_putchars(int c);
int						addToline(t_envlist *envlist, char buff);
int						removeFromline(t_envlist *envlist);
int						addTohistory(t_envlist *envlist);
void					handle_arrawkeys(t_envlist *envlist, long buff,
							int *curs, int *index);
int						handleKeys(t_envlist *envlist, long buff,
							int *curs, int *index);
int						ft_readline(t_envlist *envlist);
void					cleaning(t_envlist *envlist);
void					clean_cmdList(t_envlist *envlist);
int						addToline(t_envlist *envlist, char buff);
int						ft_isprint(int c);
void					clean_cmdList(t_envlist *env);
void					freeing(t_envlist *envlist);
void					cleaning(t_envlist *envlist);
void					shell_lvl(t_envlist *envlist);

#endif
