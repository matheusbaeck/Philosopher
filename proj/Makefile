# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/30 15:06:36 by math42            #+#    #+#              #
#    Updated: 2023/09/11 21:50:21 by mamagalh@st      ###   ########.fr        #
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
	./philo 3 7 2 2