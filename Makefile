# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/03 14:49:03 by fjoestin          #+#    #+#              #
#    Updated: 2024/09/02 14:45:00 by mkulikov         ###   ########.fr        #
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
		srcs/builtin/get_builtin_idx.c \
		srcs/parser/parser.c \
		srcs/parser/parse_cmd.c \
		srcs/parser/parse_red.c \
		srcs/executor/heredoc.c \
		srcs/executor/executer.c \
		srcs/executor/executer_utils.c \
		srcs/executor/exe_data.c \
		srcs/executor/cmd.c \
		srcs/executor/file.c \
		srcs/utils/t_llist.c \
		srcs/utils/1_utils.c \
		srcs/utils/0_utils.c \
		srcs/utils/free.c \
		srcs/lexer/0_lexer.c \
		srcs/lexer/1_lexer.c \
		srcs/lexer/2_lexer.c \
		srcs/lexer/0_expander.c \
		srcs/lexer/1_expander.c \
		srcs/lexer/get.c \
		srcs/data.c \
		srcs/env_lst.c \
		srcs/main.c \
		srcs/test.c \
		srcs/exit_err.c

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

norm:
	@norminette $(SRC)

.PHONY: start all clean fclean re
