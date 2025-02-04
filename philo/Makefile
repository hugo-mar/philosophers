# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/21 12:12:06 by hugo-mar          #+#    #+#              #
#    Updated: 2025/02/04 14:42:15 by hugo-mar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

ARCHIVE = philo.a

CC = cc

CFLAGS = -Wall -Werror -Wextra

MAKE_LIB = ar -rcs

SRCS = main.c parsing.c init.c error_handling.c dinner.c getters_and_setters.c \
		synchronization.c print.c simulator_and_monitor.c chronometration.c \
		eat_sleep_and_think.c \

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