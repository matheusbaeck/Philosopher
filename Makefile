# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: math <math@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/30 15:06:36 by math42            #+#    #+#              #
#    Updated: 2024/04/10 18:28:22 by math             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
#CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
CFLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=thread

SRC_DIR = src
OBJ_DIR = .obj

SRCS =	src/actions.c \
		src/init.c \
		src/main.c \
		src/mutex_philo_att.c \
		src/mutex_status.c \
		src/parsing.c \
		src/philo.c \
		src/time.c \
		src/cleaning.c

OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

NAME = philo

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

test1: all
	./philo 3 300 200 100

test2: all
	./philo 3 410 200 200 10 2 2

test3: all
	./philo 3 400 100 900
	
.PHONY: all clean fclean re test