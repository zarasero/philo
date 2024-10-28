# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zserobia <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/09 12:47:56 by zserobia          #+#    #+#              #
#    Updated: 2024/10/09 12:48:00 by zserobia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

NAMESC = main.c utils.c init.c check.c act.c act_1.c act_2.c

NAMESO = $(NAMESC:.c=.o)

CFLAGS = -Wall -Werror -Wextra

CC = cc

all: $(NAME)

$(NAME): $(NAMESO)
	$(CC) -o $(NAME) $(NAMESO)

%.o: %.c
	@echo "Compiling $< into $@"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(NAMESO)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: re all clean fclean
