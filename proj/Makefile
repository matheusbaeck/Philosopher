# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: math42 <math42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/30 15:06:36 by math42            #+#    #+#              #
#    Updated: 2023/09/12 00:08:34 by math42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = clang

SRCS =  main.c philo.c actions.c utils.c

OBJS = ${SRCS:.c=.o}

CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=thread

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@make clean

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

test: re
	./philo 3 1500 400 400