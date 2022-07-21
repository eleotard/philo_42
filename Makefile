# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/07 17:44:44 by eleotard          #+#    #+#              #
#    Updated: 2022/07/20 21:59:42 by eleotard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS =	main.c \
		check_parsing.c \
		check_parsing2.c \
		ft_atoi_max.c 	\
		free_stuff.c 	\
		philo_utils.c 	\

OBJS = ${SRCS:%.c=%.o}

CC = gcc

RM = rm -rf

FLAGS = -g -O3 -pthread -Wall -Wextra  -fsanitize=thread

LIBFT = -Llibft -lft

%.o: %.c 
	${CC} ${FLAGS} -c $< -o $@

all: ${NAME}

${NAME}: ${OBJS} libft/libft.a
	${CC} ${FLAGS} -o ${NAME} ${OBJS} ${LIBFT}

libft/libft.a:
	make -C libft

ft_printf/lftprintf.a:
	make -C ft_printf
	
clean:
	${RM} ${OBJS}
	make -C libft clean

fclean: clean
	${RM} ${NAME}
	make -C libft fclean

re: clean fclean all