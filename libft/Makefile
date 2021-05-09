# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/21 15:48:22 by abdait-m          #+#    #+#              #
#    Updated: 2021/05/08 23:15:11 by abdait-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FILES = ft_split.c ft_itoa.c ft_strtrim.c ft_substr.c ft_putstr_fd.c \
		ft_putchar_fd.c ft_atoi.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
		ft_isdigit.c ft_isprint.c ft_strchr.c ft_strdup.c ft_strcmp.c \
		ft_strjoin.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strrchr.c \

OBJ = $(FILES:.c=.o)

FLG = -Wall -Wextra -Werror

HEADER = ./libft.h

all: $(NAME) 

$(NAME): $(OBJ)
		@ar -rcs $(NAME) $(OBJ)

%.o:%.c 
		@gcc  -c $< $(FLG)

clean:
		@rm -f $(OBJ) $(B_OBJ)

fclean: clean
		@rm -f $(NAME)

re: fclean all
