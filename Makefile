# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/12 18:36:15 by abdait-m          #+#    #+#              #
#    Updated: 2021/03/30 10:12:00 by abdait-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

MINISHELLLIB = minishell.a

MAIN = minishell.c

LIBFT = ./libft

LIBFT_LIB = $(LIBFT)/libft.a

FILES = $(wildcard ./srcs/*.c)

HEADER = ./includes/minishell.h

OBJECT = $(FILES:.c=.o)

FLAGS = -Wextra -Werror -Wall

all: $(NAME)

$(LIBFT_LIB):
			@make -C $(LIBFT)

$(NAME): $(OBJECT) $(HEADER) $(LIBFT_LIB) $(MAIN)
			@mv *.o ./srcs
			@ar -rcs $(MINISHELLLIB) $(OBJECT)
			@gcc  $(FLAGS) $(MAIN) $(MINISHELLLIB) $(LIBFT_LIB) -o $(NAME)
			@echo "\033[36m███╗░░░███╗██╗███╗░░██╗██╗░██████╗██╗░░██╗███████╗██╗░░░░░██╗░░░░░\033[0m"
			@echo "\033[36m████╗░████║██║████╗░██║██║██╔════╝██║░░██║██╔════╝██║░░░░░██║░░░░░\033[0m"
			@echo "\033[36m██╔████╔██║██║██╔██╗██║██║╚█████╗░███████║█████╗░░██║░░░░░██║░░░░░\033[0m"
			@echo "\033[36m██║╚██╔╝██║██║██║╚████║██║░╚═══██╗██╔══██║██╔══╝░░██║░░░░░██║░░░░░\033[0m"
			@echo "\033[36m██║░╚═╝░██║██║██║░╚███║██║██████╔╝██║░░██║███████╗███████╗███████╗\033[0m"
			@echo "\033[36m╚═╝░░░░░╚═╝╚═╝╚═╝░░╚══╝╚═╝╚═════╝░╚═╝░░╚═╝╚══════╝╚══════╝╚══════╝\033[0m"
			@echo "\033[0;35;40m \t\t\t\t   A𝚞𝚝𝚑𝚘𝚛𝚜: 𝚊𝚋𝚍𝚊𝚒𝚝-𝚖 && 𝚖𝚊𝚓𝚎𝚛𝚖𝚘𝚞 \033[0m\n"
					


%.o:%.c $(HEADER)
			@gcc -c $< $(FLAGS)

clean:
			@make clean -C $(LIBFT)
			@rm -rf srcs/*.o $(LIB)
			@echo "\n\033[32mCleaning is Done!\033[0m\n"

fclean: clean
			@make fclean -C $(LIBFT)
			@rm -rf $(NAME) $(MINISHELLLIB) 

re : fclean all