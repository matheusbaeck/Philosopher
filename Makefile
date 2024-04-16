# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/10 20:08:30 by math              #+#    #+#              #
#    Updated: 2024/04/16 16:18:31 by mamagalh@st      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
#CFLAGS = -Wall -Wextra -Werror -I. -g3 -fsanitize=address
CFLAGS = -Wall -Wextra -Werror -I. #-g3 -fsanitize=thread

SRC_DIR = src
SRC_BONUS_DIR = bonus
OBJ_DIR = .obj
OBJ_BONUS_DIR = .obj_bonus

SRCS_LIST =	actions.c \
			init.c \
			main.c \
			mutex_philo_att.c \
			mutex_status.c \
			parsing.c \
			philo.c \
			time.c \
			cleaning.c

SRC_BONUS_LIST = main.c \
				parsing.c \
				time.c \
				init.c \
				wait.c \
				philo.c


SRCS = $(patsubst %.c,$(SRC_DIR)/%.c,$(SRCS_LIST))
SRC_BONUS = $(patsubst %.c,$(SRC_BONUS_DIR)/%.c,$(SRC_BONUS_LIST))

OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
OBJS_BONUS = $(patsubst $(SRC_BONUS_DIR)/%.c,$(OBJ_BONUS_DIR)/%.o,$(SRC_BONUS))

NAME = philo

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_BONUS_DIR):
	mkdir -p $(OBJ_BONUS_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_BONUS_DIR)/%.o: $(SRC_BONUS_DIR)/%.c | $(OBJ_BONUS_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(NAME)_bonus: $(OBJ_BONUS_DIR) $(OBJS_BONUS)
	$(CC) $(CFLAGS) -o $@ $(OBJS_BONUS)

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(OBJ_BONUS_DIR)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(NAME)_bonus

re: fclean all

bonus: $(NAME)_bonus

rebonus: fclean $(NAME)_bonus

test1: all
	./philo 3 310 103 207

test2: all
	./philo 3 3 310 104 10

test3: all
	./philo 4 800 200 200
	
.PHONY: all clean fclean re test
