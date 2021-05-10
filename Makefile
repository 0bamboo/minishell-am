# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/12 18:36:15 by abdait-m          #+#    #+#              #
#    Updated: 2021/05/10 13:41:39 by abdait-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

MINISHELLLIB = minishell.a

MAIN = minishell.c

LIBFT = ./libft

LIBFT_LIB = $(LIBFT)/libft.a

FILES = ./srcs/parse/fill_list_pipe.c ./srcs/parse/fill_tools.c ./srcs/parse/fill_list.c \
		./srcs/parse/input_parser.c ./srcs/parse/handle_syntax_error.c ./srcs/parse/handle_env_vars.c \
		./srcs/parse/_split_tokens.c ./srcs/parse/handle_backslash_dq.c ./srcs/parse/fill_tools_sec.c \
		./srcs/parse/_split_tools.c ./srcs/parse/handle_env_vars_tools.c ./srcs/parse/size_env_vars.c \
		./srcs/parse/_split_tools_2.c ./srcs/parse/error_tools.c ./srcs/execution/builtin.c \
		./srcs/execution/builtin_cd.c ./srcs/execution/builtin_env.c ./srcs/execution/builtin_export.c \
		./srcs/execution/builtin_unset.c ./srcs/execution/builtin_utils.c ./srcs/execution/history.c \
		./srcs/execution/io_redir.c ./srcs/execution/pipe.c ./srcs/execution/utils.c ./srcs/execution/clean.c

HEADER = ./includes/minishell.h

OBJECT = $(FILES:.c=.o)

FLAGS = -Wextra -Werror -Wall

HIS = -ltermcap

all: $(NAME)

$(LIBFT_LIB):
			@make -C $(LIBFT)

$(NAME): $(OBJECT) $(HEADER) $(LIBFT_LIB) $(MAIN) $(FILES)
			@ar -rcs $(MINISHELLLIB) $(OBJECT)
			@gcc  $(FLAGS) $(MAIN) $(MINISHELLLIB) $(LIBFT_LIB) $(HIS) -o $(NAME)
			@echo "\033[36m███╗░░░███╗██╗███╗░░██╗██╗░██████╗██╗░░██╗███████╗██╗░░░░░██╗░░░░░\033[0m"
			@echo "\033[36m████╗░████║██║████╗░██║██║██╔════╝██║░░██║██╔════╝██║░░░░░██║░░░░░\033[0m"
			@echo "\033[36m██╔████╔██║██║██╔██╗██║██║╚█████╗░███████║█████╗░░██║░░░░░██║░░░░░\033[0m"
			@echo "\033[36m██║╚██╔╝██║██║██║╚████║██║░╚═══██╗██╔══██║██╔══╝░░██║░░░░░██║░░░░░\033[0m"
			@echo "\033[36m██║░╚═╝░██║██║██║░╚███║██║██████╔╝██║░░██║███████╗███████╗███████╗\033[0m"
			@echo "\033[36m╚═╝░░░░░╚═╝╚═╝╚═╝░░╚══╝╚═╝╚═════╝░╚═╝░░╚═╝╚══════╝╚══════╝╚══════╝\033[0m"
			@echo "\033[35m \t\t\t\t   A𝚞𝚝𝚑𝚘𝚛𝚜: 𝚊𝚋𝚍𝚊𝚒𝚝-𝚖 && 𝚖𝚊𝚓𝚎𝚛𝚖𝚘𝚞 \033[0m\n"
					


%.o:%.c $(HEADER)
			@gcc -c $< $(FLAGS) -o $@

clean:
			@make clean -C $(LIBFT)
			@rm -rf srcs/parse/*.o srcs/execution/*.o $(LIB)
			@echo "\n\033[32mCleaning is Done!\033[0m\n"

fclean: clean
			@make fclean -C $(LIBFT)
			@rm -rf $(NAME) $(MINISHELLLIB) 

re : fclean all