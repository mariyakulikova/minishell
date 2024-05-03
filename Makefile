# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/03 14:49:03 by fjoestin          #+#    #+#              #
#    Updated: 2024/05/03 17:51:53 by mkulikov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CCFLAGS = -Wextra -Wall -Werror
RM = rm -f
DEBUG = -g

HEADDIR = .
HEADERS = minishell.h

SRCS =	0_utils.c \
		echo.c \
		main.c \
		env_lst.c \
		data.c

OBJSDIR = ./objs/
OBJSLIST = $(SRCS:.c=.o)
OBJS = $(addprefix $(OBJSDIR), $(OBJSLIST))

LIBFTDIR = ./libft/
LIBFT = $(LIBFTDIR)libft.a

READLINE = -lreadline

LIBS = -L${LIBFTDIR} -lft ${READLINE}
INCS = -I${HEADDIR} -I${LIBFTDIR}

all: $(NAME)

$(NAME): $(LIBFT) $(OBJSDIR) $(OBJS)
	$(CC) $(FLAGS) $(DEBUG) $(OBJS) -o $@ $(LIBS) $(INCS)

$(LIBFT):
	make -C $(LIBFTDIR)

$(OBJSDIR):
	mkdir -p $(OBJSDIR)

$(OBJSDIR)%.o: %.c $(HEADERS)
	$(CC) $(FLAGS) $(DEBUG) $(INCS) -c $< -o $@

clean:
	$(RM) -r $(OBJSDIR)
	make -C $(LIBFTDIR) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re
