# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/03 14:49:03 by fjoestin          #+#    #+#              #
#    Updated: 2024/08/18 12:05:37 by mkulikov         ###   ########.fr        #
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
		srcs/parser/parser.c \
		srcs/parser/parse_cmd.c \
		srcs/parser/parse_red.c \
		srcs/parser/heredoc.c \
		srcs/executor/executer.c \
		srcs/0_lexer.c \
		srcs/0_utils.c \
		srcs/data.c \
		srcs/env_lst.c \
		srcs/main.c \
		srcs/1_lexer.c \
		srcs/get.c \
		srcs/test.c \
		srcs/0_expander.c \
		srcs/1_expander.c


OBJ = $(patsubst %.c,$(OBJ_DIR)%.o,$(SRC))

start:
	@make all
$(LIBFT):
	@make -C ./libft

all: $(NAME)
$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(FLAGS) $(INC) $(OBJ) $(LIBFT) $(READFLAG) -o $(NAME)
$(OBJ_DIR)%.o:	  %.c
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) $(INC) -c $< -o $@

clean:
	@$(RM) -r $(OBJ_DIR)
	@make clean -C ./libft

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(LIBFT)

re: fclean all

norminette:
	@norminette $(SRC)

.PHONY: start all clean fclean re
