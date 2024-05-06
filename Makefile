# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fjoestin <fjoestin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/03 14:49:03 by fjoestin          #+#    #+#              #
#    Updated: 2024/05/06 22:58:25 by fjoestin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT = ./libft/libft.a
INC = inc/
OBJ_DIR = obj/
CC = cc
FLAGS = -g -Wall -Wextra -Werror -I
READFLAG = -lreadline
RM = rm -f
SRC =   srcs/builtin/cd.c \
		srcs/builtin/echo.c \
		srcs/builtin/env.c \
		srcs/builtin/exit.c \
		srcs/builtin/export.c \
		srcs/builtin/pwd.c \
		srcs/builtin/unset.c \
		srcs/0_executer.c \
		srcs/0_lexer.c \
		srcs/0_parser.c \
		srcs/0_utils.c \
		srcs/data.c \
		srcs/env_lst.c \
		srcs/main.c \
		
		
OBJ = $(patsubst %.c,$(OBJ_DIR)%.o,$(SRC))

start:
	@make all
$(LIBFT):
	@make -C ./lib/libft

all: $(NAME)
$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(FLAGS) $(INC) $(OBJ) $(LIBFT) $(READFLAG) -o $(NAME)
$(OBJ_DIR)%.o:	  %.c
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) $(INC) -c $< -o $@

clean:
	@$(RM) -r $(OBJ_DIR)
	@make clean -C ./lib/libft

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(LIBFT)

re: fclean all

norminette:
	@norminette $(SRC)

.PHONY: start all clean fclean re