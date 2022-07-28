# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/07 17:44:44 by eleotard          #+#    #+#              #
#    Updated: 2022/07/28 17:56:07 by eleotard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS =	main.c 				\
		check_parsing.c 	\
		check_parsing2.c	\
		check_input.c 		\
		ft_atoi_max.c 		\
		free_stuff.c 		\
		free_mutex.c 		\
		philo_utils.c 		\
		actions.c 			\
		init.c				\
		monitor.c			\
		time.c				\
		error_thread.c 		\
		threads.c 			\
		print.c 			\
		forks.c 			\
		ft_atoi.c			\
		ft_strlen.c			\
		ft_substr.c			\
		ft_putchar_fd.c		\
		ft_putstr_fd.c 		\
		ft_split.c 			\

OBJS = ${SRCS:%.c=%.o}

CC = gcc

RM = rm -rf

FLAGS = -O3 -pthread -Wall -Wextra -Werror -g3 -fsanitize=address

%.o: %.c
	${CC} ${FLAGS} -c $< -o $@

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${FLAGS} -o $@ $^
	
clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY : all clean fclean re
