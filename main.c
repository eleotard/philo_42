/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 02:19:03 by eleotard          #+#    #+#             */
/*   Updated: 2022/07/09 21:01:28 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int ft_get_time()
{
	struct timeval	current_time;
	long int		time;

	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

void	*routine(void	*da)
{
	t_philo		*philo;
	long int	start;
	
	philo = (t_philo *)da;

	pthread_mutex_lock(philo->mutex);
	start = philo->general->start;
	pthread_mutex_unlock(philo->mutex);

	while (1)
	{
		pthread_mutex_lock(philo->can_print);
		if (*philo->print == 0)
		{
			pthread_mutex_unlock(philo->can_print);
			break ;
		}
		pthread_mutex_unlock(philo->can_print);
		pthread_mutex_lock(philo->forks.f_fork);
		pthread_mutex_lock(philo->forks.s_fork);
		//printf("\t\ttruc = %ld\n", ft_get_time() - start - philo->last_meal);
		//printf("%ld %d has taken a fork\n", (ft_get_time() - start), philo->philo_nb);
		//printf("%ld %d has taken a fork\n", (ft_get_time() - start), philo->philo_nb);
		pthread_mutex_lock(philo->mutex);
		philo->last_meal = (ft_get_time() - start);
		pthread_mutex_unlock(philo->mutex);
		pthread_mutex_lock(philo->can_print);
		if (*philo->print == 1)
			printf("%ld %d is eating\n", (ft_get_time() - start), philo->philo_nb);
		pthread_mutex_unlock(philo->can_print);
		usleep((philo->general->time_to_eat) * 1000);
		//printf("%ld\t %d has let down a fork\n", (ft_get_time() - pthread_mutex_lock(philo->can_print)start), philo->philo_nb);
		//printf("%ld\t %d has let down a fork\n", (ft_get_time() - start), philo->philo_nb);
		pthread_mutex_unlock(philo->forks.f_fork);
		pthread_mutex_unlock(philo->forks.s_fork);
		pthread_mutex_lock(philo->can_print);
		if (*philo->print == 1)
			printf("%ld %d is sleeping\n", (ft_get_time() - start), philo->philo_nb);
		pthread_mutex_unlock(philo->can_print);
		usleep((philo->general->time_to_sleep) * 1000);
		pthread_mutex_lock(philo->can_print);
		if (*philo->print == 1)
			printf("%ld %d is thinking\n", (ft_get_time() - start), philo->philo_nb);
		pthread_mutex_unlock(philo->can_print);
		//pthread_mutex_unlock(philo->can_print);
	}	
	return (NULL);
}

void	ft_init_general(t_general *general, int argc, char **argv)
{
	char	**tab;

	if (argc == 2)
	{
		tab = ft_split(argv[1], ' ');
		general->nb_of_philo = ft_atoi(tab[0]);
		general->time_to_die = ft_atoi(tab[1]);
		general->time_to_eat = ft_atoi(tab[2]);
		general->time_to_sleep = ft_atoi(tab[3]);
		general->nb_of_time = ft_atoi(tab[4]); // si ya que 4 ar, = 0, si 5 = arg 
		ft_free_tab(tab);
	}
	else
	{
		general->nb_of_philo = ft_atoi(argv[1]);
		general->time_to_die = ft_atoi(argv[2]);
		general->time_to_eat = ft_atoi(argv[3]);
		general->time_to_sleep = ft_atoi(argv[4]);
		general->nb_of_time = ft_atoi(argv[5]);
	}
}

t_philo	*ft_init_philo_structs(t_general *general, pthread_mutex_t	*mutex, int *print, pthread_mutex_t	*can_print)
{
	t_philo				*bigdata;
	t_philo				*philo;
	pthread_mutex_t		*tab_mut;
	int					i;
	
	bigdata = malloc(sizeof(t_philo) * general->nb_of_philo);
	if (!bigdata)
		return (NULL);
	tab_mut = malloc(sizeof(pthread_mutex_t) * general->nb_of_philo);
	if (!tab_mut)
		return (free_rt_null(bigdata));
	i = -1;
	while (++i < general->nb_of_philo)
	{
		if(pthread_mutex_init(&tab_mut[i], NULL) != 0)
			return (NULL);
	}
	philo = bigdata;
	i = -1;
	while (++i < general->nb_of_philo)
	{
		philo->tab_mut = tab_mut;
		philo->mutex = mutex;
		philo->can_print = can_print;
		philo->print = print;
		philo->general = general;
		philo->philo_nb = i;
		philo->last_meal = 0;
		philo->state = 0;
		philo++;
	}
	return (bigdata);
}

void	ft_init_philo_forks(t_philo *bigdata)
{
	t_philo	*philo;
	int 	i;

	i = -1;
	philo = bigdata;

	while (++i < bigdata->general->nb_of_philo)
	{
		if (philo->philo_nb == 0) //donc le premier
		{
			philo->forks.f_fork = &philo->tab_mut[0];
			philo->forks.s_fork = &philo->tab_mut[(philo->general->nb_of_philo) - 1];
		}
		else if (philo->philo_nb == (bigdata->general->nb_of_philo - 1))
		{
			philo->forks.f_fork = &philo->tab_mut[0];
			philo->forks.s_fork = &philo->tab_mut[philo->philo_nb];
		}
		else //les autres
		{
			philo->forks.f_fork = &philo->tab_mut[philo->philo_nb];
			philo->forks.s_fork = &philo->tab_mut[(philo->philo_nb) - 1];
		}
		philo++;
	}
}

void	ft_check_philo_states(t_philo *bigdata, pthread_mutex_t	*can_print)
{
	int		i;
	t_philo *philo;
	//t_philo *buff;
	int 	state;

	state = 0;
	while (1)
	{
		i = -1;
		philo = bigdata;
		while (++i < bigdata->general->nb_of_philo)
		{
			pthread_mutex_lock(philo->mutex);
			if (ft_get_time() - philo->general->start - philo->last_meal
				>= philo->general->time_to_die)
			{
				printf("checher ; %ld\n", ft_get_time() - philo->general->start - philo->last_meal);
				state = DEAD;
				pthread_mutex_unlock(philo->mutex);
				break ;
			}
			pthread_mutex_unlock(philo->mutex);
			philo++;
		}
		if (state == DEAD)
		{
			pthread_mutex_lock(can_print);
			*philo->print = 0;
			pthread_mutex_unlock(can_print);
			printf("%ld %d is dead\n", (ft_get_time() - philo->general->start)
				,philo->philo_nb);
			//pthread_mutex_lock(can_print);
			break ;
		}
	}
}

int	main(int argc, char **argv)
{
	int				i;
	int				print;
	t_philo			*bigdata;
	t_general		general;
	pthread_mutex_t	mutex;
	pthread_mutex_t	can_print;


	print = 1;
	if (ft_check_parsing(argc, argv) == ERROR)
		return (0);
	ft_init_general(&general, argc, argv);
	if (ft_check_correct_input(argc, argv, &general) == ERROR)
		return (-1);
	/*mutex = malloc(sizeof(pthread_mutex_t));
	if(!mutex)
		return (-1);*/
	if (pthread_mutex_init(&mutex, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&can_print, NULL) != 0)
		return (-1);
	bigdata = ft_init_philo_structs(&general, &mutex, &print, &can_print);
	if (!bigdata)
	{
		pthread_mutex_destroy(&mutex);
		//free(mutex);
		return (-1);
	}
	ft_init_philo_forks(bigdata);
	i = -1;
	pthread_mutex_lock(&mutex);
	while (++i < general.nb_of_philo)
	{
		if (pthread_create(&bigdata[i].th, NULL, &routine, &bigdata[i])) //!= 0
			return (ft_free_all(bigdata, &mutex));
		printf("Thread %d has started execution\n", bigdata[i].philo_nb);
	}
	general.start = ft_get_time();
	pthread_mutex_unlock(&mutex); 

	ft_check_philo_states(bigdata, &can_print);

	i = -1;
	while (++i < general.nb_of_philo)
	{
		if (pthread_join(bigdata[i].th, NULL) != 0) //attend que le thread soit termine pour quitter le programme
			return (ft_free_all(bigdata, &mutex));
		printf("Thread %d has finished execution\n", bigdata[i].philo_nb);
	}
	ft_free_all(bigdata, &mutex);
	//pthread_mutex_unlock(&can_print);
	pthread_mutex_destroy(&can_print);
	return (0);
}
