/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:24:47 by eleotard          #+#    #+#             */
/*   Updated: 2022/07/09 19:52:25 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <stddef.h>
# include <pthread.h>
# include <sys/time.h>

# include "libft/libft.h"

# define ERROR	-1
# define DEAD	3

typedef struct s_general
{
	int	nb_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nb_of_time;
	long int	start;
}	t_general;

typedef struct s_forks
{
	pthread_mutex_t *r_fork;
	pthread_mutex_t	*l_fork;
}	t_forks;


typedef struct s_philo
{
	pthread_t		th;
	pthread_mutex_t	*tab_mut;
	pthread_mutex_t	*mutex;
	t_general		*general;
	t_forks			forks;
	long int		last_eat;
	int				state;
	int				philo_nb;
	int				tms;
}	t_philo;

typedef struct s_lst
{
	int		content;
	void	*next;
}	t_lst;

typedef struct s_rdm
{
	int		i;
	int		j;
	int		k;
	char	**tab;
}	t_rdm;

/*PARSING*/
int	ft_check_parsing(int argc, char **argv);
int ft_check_arg(int argc, char **argv);
int	ft_check_correct_caracters(char **argv);
int	ft_check_is_digit(t_rdm *va);
int	ft_check_correct_int(char **argv);
int	ft_check_overflow(char **argv);
int	ft_atoi_max(const char *nptr);
int	ft_previous_check(int *sign, const char *nptr);
int	ft_check_arg_2(char **argv);
int	ft_check_arg_5(char **argv);
int	ft_check_arg_6(char **argv);
int	ft_check_correct_input(int argc, char **argv, t_general *general);

/*FREE*/
char	**ft_free_tab(char **tab);
t_philo	*free_rt_null(t_philo *data);
int		ft_free_all(t_philo *bigdata);

/*UTILS*/
int	ft_find_nb_of_arg(char *str);

#endif