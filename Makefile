# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/28 06:15:21 by yochoi            #+#    #+#              #
#    Updated: 2020/07/16 20:37:00 by yochoi           ###   ########.fr        #
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

SRC_DIR = ./srcs/
SRCS = $(addprefix $(SRC_DIR), $(SRC))
SRC =	main.c \
		pwd.c \
		read_command.c

OBJ_DIR = ./obj/
OBJS = $(addprefix $(OBJ_DIR), $(OBJ))
OBJ = $(SRC:.c=.o)

INC_DIR = includes

LIBFT_DIR = libft
LIBFT_INC = libft/includes
LIBFT_LIB = -L $(LIBFT_DIR) -lft

all: libft_make $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFT_LIB) $(MLX_LIB)
	@echo "$(_GREEN)Program '$(NAME)' compiled. $(_END)"
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) -o $@ -c $<
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

libft_make:
	@make -C libft

clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJ_DIR)
	@make -C libft/ fclean
	@echo "$(_RED)'"obj"' has been deleted. $(_END)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(_RED)'"$(NAME)"' has been deleted. $(_END)"