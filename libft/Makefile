# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/17 20:36:22 by yochoi            #+#    #+#              #
#    Updated: 2020/07/16 20:31:31 by yochoi           ###   ########.fr        #
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

NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR)

SRC_DIR = ./srcs/
SRCS = $(addprefix $(SRC_DIR), $(SRC))
SRC =		ft_abs.c \
			ft_atoi.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_isspace.c \
			ft_itoa.c \
			ft_memccpy.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_putstr_fd.c \
			ft_split.c \
			ft_split_len.c \
			ft_split_del.c \
			ft_strchr.c \
			ft_strdup.c \
			ft_strjoin.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strnew.c \
			ft_strmapi.c \
			ft_strcmp.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_strdel.c \
			ft_strrchr.c \
			ft_strtrim.c \
			ft_substr.c \
			ft_substr.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstmap.c \
			get_next_line.c \

PRINTF =	./ft_printf/pf_check.c \
			./ft_printf/pf_itoa.c \
			./ft_printf/pf_itoa_base.c \
			./ft_printf/pf_itoa_base_u.c \
			./ft_printf/pf_numlen.c \
			./ft_printf/pf_putchar.c \
			./ft_printf/pf_putnbr.c \
			./ft_printf/pf_puthex.c \
			./ft_printf/pf_putstr.c \
			./ft_printf/pf_strlen.c \
			./ft_printf/pf_str.c \
			./ft_printf/pf_print_big_x.c \
			./ft_printf/pf_print_c.c \
			./ft_printf/pf_print_d.c \
			./ft_printf/pf_print_flag.c \
			./ft_printf/pf_print_p.c \
			./ft_printf/pf_print_s.c \
			./ft_printf/pf_print_small_x.c \
			./ft_printf/pf_print_u.c \
			./ft_printf/pf_print_percent.c \
			./ft_printf/pf_read_str.c \
			./ft_printf/printf.c

OBJ_DIR = ./obj/
OBJS = $(addprefix $(OBJ_DIR), $(OBJ))
OBJ = $(SRC:.c=.o)

INC_DIR = ./includes/

all: ft_printf_make $(NAME)

$(NAME): $(OBJS)
	@echo "$(_GREEN)All files compiled. $(_END)"
	@ar rcs $(NAME) $(OBJ_DIR)*
	@echo "$(_GREEN)Library '$(NAME)' compiled. $(_END)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) -c $< -o $@

ft_printf_make:
	@$(CC) $(CFLAGS) -c $(PRINTF)
	@mkdir -p $(OBJ_DIR)
	@mv ./*.o ./$(OBJ_DIR)

clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJ_DIR)
	@echo "$(_RED)'"libft/obj"' has been deleted. $(_END)"

fclean: clean 
	@rm -f $(NAME)
	@echo "$(_RED)'"$(NAME)"' has been deleted. $(_END)"

re: fclean all
