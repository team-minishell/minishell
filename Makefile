# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nahangyeol <nahangyeol@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/28 06:15:21 by yochoi            #+#    #+#              #
#    Updated: 2020/08/07 21:00:55 by nahangyeol       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## MAKEFILE ##

# COLORS #

# This is a minimal set of ANSI color codes
_END		=	\033[0;0m
_BOLD		=	\033[0;1m
_UNDER		=	\033[0;4m
_REV		=	\033[0;7m

# Colors
_GREY		=	\033[0;30m
_RED		=	\033[0;31m
_GREEN		=	\033[0;32m
_YELLOW		=	\033[0;33m
_BLUE		=	\033[0;34m
_PURPLE		=	\033[0;35m
_CYAN		=	\033[0;36m
_WHITE		=	\033[0;37m

# Inverted, i.e. colored backgrounds
_IGREY		=	\033[0;40m
_IRED		=	\033[0;41m
_IGREEN		=	\033[0;42m
_IYELLOW	=	\033[0;43m
_IBLUE		=	\033[0;44m
_IPURPLE	=	\033[0;45m
_ICYAN		=	\033[0;46m
_IWHITE		=	\033[0;47m

# **************************************************************************** #

.PHONY: all clean fclean re

NAME = minishell

CC = gcc
CFLAGS = -I $(INC_DIR) -I $(LIBFT_INC) -g

INC_DIR = includes

LIBFT_INC = libft/includes

all: make_libft make_obj $(NAME)

$(NAME):
	@$(CC) $(CFLAGS) -o $@ ./obj/* -L libft -lft
	@echo "$(_GREEN)Program '$(NAME)' compiled. $(_END)"

make_obj:
	@mkdir -p ./obj
	@$(CC) $(CFLAG) -c ./srcs/builtin/execute_cd.c			-o ./obj/execute_cd.o			-I $(INC_DIR) -I $(LIBFT_INC)
	@$(CC) $(CFLAG) -c ./srcs/builtin/execute_echo.c		-o ./obj/execute_echo.o			-I $(INC_DIR) -I $(LIBFT_INC)
	@$(CC) $(CFLAG) -c ./srcs/builtin/execute_env.c			-o ./obj/execute_env.o			-I $(INC_DIR) -I $(LIBFT_INC)
	@$(CC) $(CFLAG) -c ./srcs/builtin/execute_export.c		-o ./obj/execute_export.o		-I $(INC_DIR) -I $(LIBFT_INC)
	@$(CC) $(CFLAG) -c ./srcs/builtin/execute_pwd.c			-o ./obj/execute_pwd.o			-I $(INC_DIR) -I $(LIBFT_INC)
	@$(CC) $(CFLAG) -c ./srcs/builtin/execute_unset.c		-o ./obj/execute_unset.o		-I $(INC_DIR) -I $(LIBFT_INC)
	@$(CC) $(CFLAG) -c ./srcs/utils/split_except_quote.c	-o ./obj/split_except_quote.o	-I $(INC_DIR) -I $(LIBFT_INC)
	@$(CC) $(CFLAG) -c ./srcs/utils/split_double_arrow.c	-o ./obj/split_double_arrow.o	-I $(INC_DIR) -I $(LIBFT_INC)
	@$(CC) $(CFLAG) -c ./srcs/convert_str.c					-o ./obj/convert_str.o			-I $(INC_DIR) -I $(LIBFT_INC)
	@$(CC) $(CFLAG) -c ./srcs/create_job.c					-o ./obj/create_job.o			-I $(INC_DIR) -I $(LIBFT_INC)
	@$(CC) $(CFLAG) -c ./srcs/execution.c					-o ./obj/execution.o			-I $(INC_DIR) -I $(LIBFT_INC)
	@$(CC) $(CFLAG) -c ./srcs/handle_signal.c				-o ./obj/handle_signal.o		-I $(INC_DIR) -I $(LIBFT_INC)
	@$(CC) $(CFLAG) -c ./srcs/main.c						-o ./obj/main.o					-I $(INC_DIR) -I $(LIBFT_INC)
	@$(CC) $(CFLAG) -c ./srcs/manage_list.c					-o ./obj/manage_list.o			-I $(INC_DIR) -I $(LIBFT_INC)
	@$(CC) $(CFLAG) -c ./srcs/parse_line.c					-o ./obj/parse_line.o			-I $(INC_DIR) -I $(LIBFT_INC)
	@$(CC) $(CFLAG) -c ./srcs/parsing.c						-o ./obj/parsing.o				-I $(INC_DIR) -I $(LIBFT_INC)
	@$(CC) $(CFLAG) -c ./srcs/pipe.c						-o ./obj/pipe.o					-I $(INC_DIR) -I $(LIBFT_INC)
	@$(CC) $(CFLAG) -c ./srcs/read_line.c					-o ./obj/read_line.o			-I $(INC_DIR) -I $(LIBFT_INC)
	@$(CC) $(CFLAG) -c ./srcs/redirect.c					-o ./obj/redirect.o				-I $(INC_DIR) -I $(LIBFT_INC)

make_libft:
	@make -C libft

clean:
	@rm -rf obj
	@make -C libft/ fclean
	@echo "$(_RED)'"obj"' has been deleted. $(_END)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(_RED)'"$(NAME)"' has been deleted. $(_END)"

re: fclean all