# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/12 18:36:15 by abdait-m          #+#    #+#              #
#    Updated: 2021/03/13 14:07:23 by abdait-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIB = libshell.a

MAIN = minishell.c

FILES = $(wildcard ./srcs/*.c)

HEADER = ./includes/minishell.h

OBJECT = $(FILES:.c=.o)

FLAGS = -Wextra -Werror -Wall

all: $(NAME)

$(NAME): $(OBJECT) $(HEADER)
	@mv *.o ./srcs
	@ar -rcs $(LIB) $(OBJECT)
	@gcc  $(FLAGS) $(MAIN) $(LIB) -o $(NAME)
	@echo "\n\033[36m***** HAJIME !! ***** \033[0m\n"


%.o:%.c $(HEADER)
	@gcc -c $< $(FLAGS)

clean:
	@rm -rf srcs/*.o $(LIB)
	@echo "\n\033[32mCleaning is Done!\033[0m\n"

fclean: clean
	@rm -rf $(NAME)

re : fclean all