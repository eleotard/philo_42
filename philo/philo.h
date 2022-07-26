/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:24:47 by eleotard          #+#    #+#             */
/*   Updated: 2022/07/26 17:43:30 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <stddef.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

# include "libft/libft.h"

# define ERROR	-1
# define EAT	1
# define SLEEP	2
# define THINK	4
# define DEAD	3
# define OVER	5

typedef struct s_general
{
	int					nb_of_philo;
	unsigned long long	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	int					nb_of_time;
	unsigned long long	start;
}	t_general;

typedef struct s_forks
{
	pthread_mutex_t	*f_fork;
	pthread_mutex_t	*s_fork;
}	t_forks;

typedef struct s_mutex
{
	pthread_mutex_t	can_print;
	pthread_mutex_t	m_start;
	pthread_mutex_t	m_start_2;
	pthread_mutex_t	m_meal;
}	t_mutex;

typedef struct s_philo
{
	pthread_t			th;
	pthread_mutex_t		*tab_mut;
	t_mutex				*mut;
	int					*print;
	t_general			*general;
	t_forks				forks;
	unsigned long long	last_meal;
	int					philo_nb;
	int					state;
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
int					ft_check_parsing(int argc, char **argv);
int					ft_check_arg(int argc, char **argv);
int					ft_check_correct_caracters(char **argv);
int					ft_check_is_digit(t_rdm *va);
int					ft_check_correct_int(char **argv);
int					ft_check_overflow(char **argv);
int					ft_atoi_max(const char *nptr);
int					ft_previous_check(int *sign, const char *nptr);
int					ft_check_arg_2(char **argv);
int					ft_check_arg_5(char **argv);
int					ft_check_arg_6(char **argv);
int					ft_check_correct_input(int argc, char **argv,
						t_general *general);

/*FREE*/
char				**ft_free_tab(char **tab);
t_philo				*free_rt_null(t_philo *data);
int					ft_free_all(t_philo *bigdata);
void				*ft_destroy_mutexs(t_mutex *mut);
void				*ft_destroy_mutexs_2(pthread_mutex_t *m_start,
						pthread_mutex_t *can_print, pthread_mutex_t *m_meal,
						pthread_mutex_t *m_start_2);
void				*free_destroy_tabmut(pthread_mutex_t *tab_mut, int k);
void				*ft_destroy_all_mutexs(pthread_mutex_t *tab_mut, int k,
						t_mutex *mut);

/*UTILS*/
int					ft_find_nb_of_arg(char *str);

/*ACTIONS*/
void				ft_eat(t_philo *philo);
void				ft_sleep(t_philo *philo);
void				ft_think(t_philo *philo);

/*INIT*/
void				ft_init_general(t_general *general, int argc, char **argv);
int					ft_init_mutex_struct(t_mutex *mut);
t_philo				*ft_init_philo_structs(t_general *general, t_mutex	*mutex,
						int *print);
pthread_mutex_t		*ft_init_mut_tab(t_general *general);
void				ft_attribute_philo_forks(t_philo *bigdata);

/*PRINT*/
void				ft_print_output(t_philo *philo, char *str);

/*TIME*/
unsigned long long	ft_get_time(void);
unsigned long long	ft_get_time_micro(void);
void				ft_myusleep(unsigned long long ms);

/*MONITOR*/
void				ft_check_philo_states(t_philo *bigdata);
int					ft_state_over_or_dead(t_philo *philo, int state);
t_philo				*ft_make_death_check(t_philo *philo, int *i, int *state);

/*ERROR THREAD*/
int					ft_deal_with_ptc(t_philo *bigdata, int i);
int					ft_deal_with_ptj(t_philo *bigdata);

/*THREADS FONCTIONS*/
int					ft_create_threads(t_philo *bigdata);
int					ft_join_threads(t_philo *bigdata);
void				*routine(void	*da);
int					ft_check_thread_error_in_routine(t_philo *philo);
int					ft_check_nb_of_meals(t_philo *philo, int meal);
void				ft_mutex_starts_threads(t_philo *philo);
void				ft_print_output(t_philo *philo, char *str);
int					ft_check_print(t_philo *philo);

#endif