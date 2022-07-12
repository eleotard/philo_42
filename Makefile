# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/07 17:44:44 by eleotard          #+#    #+#              #
#    Updated: 2022/07/09 18:13:45 by eleotard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS =	main.c \
		check_parsing.c \
		check_parsing2.c \
		ft_atoi_max.c 	\
		free_stuff.c 	\

OBJS = ${SRCS:%.c=%.o}

CC = gcc

RM = rm -rf

FLAGS = -Wall -Wextra -Werror -pthread -g

LIBFT = -Llibft -lft

%.o: %.c 
	${CC} ${FLAGS} -c $< -o $@

all: ${NAME}

${NAME}: ${OBJS} libft/libft.a
	${CC} ${FLAGS} -o ${NAME} ${OBJS} ${LIBFT}

libft/libft.a:
	make -C libft
	
clean:
	${RM} ${OBJS}
	make -C libft clean

fclean: clean
	${RM} ${NAME}
	make -C libft fclean

re: fclean all