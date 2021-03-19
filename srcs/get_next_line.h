/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 18:18:02 by majermou          #+#    #+#             */
/*   Updated: 2021/03/13 17:10:53 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>


#define BUFFER_SIZE 100
int			get_next_line(int fd, char **line);
int			check_break_line(char *tab);
int			ft_strlen(const char *str);
int			check_previous_read(char **line, char *tab);
char		*ft_strjoin(char const *line, char const *tab);
int			dealocate(char **line, char **tab, int ret, int var_bol);
int			error_check(int fd, char **line, char **tab);
void		for_next_read(char **tab);
char		*ft_strdup(const char *src);

#endif
