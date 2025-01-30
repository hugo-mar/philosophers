# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/21 12:12:06 by hugo-mar          #+#    #+#              #
#    Updated: 2025/01/30 23:08:05 by hugo-mar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

ARCHIVE = philo.a

CC = cc

CFLAGS = -Wall -Werror -Wextra

MAKE_LIB = ar -rcs

SRCS_DIR = sources

SRCS = $(SRCS_DIR)/main.c $(SRCS_DIR)/parsing.c $(SRCS_DIR)/init.c \
		$(SRCS_DIR)/error_handling.c $(SRCS_DIR)/dinner.c \
		$(SRCS_DIR)/getters_and_setters.c $(SRCS_DIR)/synchronization.c\
		$(SRCS_DIR)/print.c $(SRCS_DIR)/simulator_and_monitor.c \
		$(SRCS_DIR)/chronometration.c $(SRCS_DIR)/eat_sleep_and_think.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

$(ARCHIVE): $(OBJS)
	$(MAKE_LIB) $(ARCHIVE) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(ARCHIVE)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re