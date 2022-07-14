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

	if ((philo->philo_nb)%2 == 1)
			usleep(1000);
	while (1)
	{
		pthread_mutex_lock(philo->forks.l_fork);
		pthread_mutex_lock(philo->forks.r_fork);
		//printf("\t\ttruc = %ld\n", ft_get_time() - start - philo->last_eat);
		//printf("%ld\t %d has taken a fork\n", (ft_get_time() - start), philo->philo_nb);
		//printf("%ld\t %d has taken a fork\n", (ft_get_time() - start), philo->philo_nb);
		philo->last_eat = (ft_get_time() - start);
		printf("%ld %d is eating\n", (ft_get_time() - start), philo->philo_nb);
		usleep((philo->general->time_to_eat) * 1000);
		//printf("\t\ttime to eat = %d\n", philo->general->time_to_eat);
		//printf("%ld\t %d has let down a fork\n", (ft_get_time() - start), philo->philo_nb);
		//printf("%ld\t %d has let down a fork\n", (ft_get_time() - start), philo->philo_nb);
		pthread_mutex_unlock(philo->forks.l_fork);
		pthread_mutex_unlock(philo->forks.r_fork);
		printf("%ld %d is sleeping\n", (ft_get_time() - start), philo->philo_nb);
		//printf("\t\ttime to sleep = %d\n", philo->general->time_to_sleep);
		usleep((philo->general->time_to_sleep) * 1000);
		printf("%ld %d is thinking\n", (ft_get_time() - start), philo->philo_nb);
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

t_philo	*ft_init_philo_structs(t_general *general, pthread_mutex_t	*mutex)
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
		philo->general = general;
		philo->philo_nb = i;
		philo->last_eat = 0;
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
			philo->forks.l_fork = &philo->tab_mut[0];
			philo->forks.r_fork = &philo->tab_mut[(philo->general->nb_of_philo) - 1];
		}
		else //les autres
		{
			philo->forks.l_fork = &philo->tab_mut[philo->philo_nb];
			philo->forks.r_fork = &philo->tab_mut[(philo->philo_nb) - 1];
		}
		philo++;
	}
}

int	ft_check_philo_states(t_philo *bigdata)
{
	int		i;
	t_philo *philo;

	while (1)
	{
		i = 0;
		philo = bigdata;
		while (++i < bigdata->general->nb_of_philo)
		{
			if (ft_get_time() - philo->general->start - philo->last_eat
				>= philo->general->time_to_die)
			{
				philo->state = DEAD;
				break ;
			}
			philo++;
		}
		if (philo->state == DEAD)
		{
			printf("%ld %d is dead\n", (ft_get_time() - philo->general->start)
				,philo->philo_nb);
			break ;
		}
	}
	return (DEAD);
}

int	main(int argc, char **argv)
{
	int				i;
	t_philo			*bigdata;
	t_general		general;
	pthread_mutex_t	mutex;

	
	if (ft_check_parsing(argc, argv) == ERROR)
		return (0);
	ft_init_general(&general, argc, argv);
	if (ft_check_correct_input(argc, argv, &general) == ERROR)
		return (-1);
	if (pthread_mutex_init(&mutex, NULL) != 0)
		return (-1);
	bigdata = ft_init_philo_structs(&general, &mutex);
	if (!bigdata)
	{
		pthread_mutex_destroy(&mutex);
		return (-1);
	}
	ft_init_philo_forks(bigdata);
	i = -1;
	pthread_mutex_lock(&mutex);
	while (++i < general.nb_of_philo)
	{
		if (pthread_create(&bigdata[i].th, NULL, &routine, &bigdata[i])) //!= 0
			return (ft_free_all(bigdata));
		printf("Thread %d has started execution\n", bigdata[i].philo_nb);
	}
	general.start = ft_get_time();
	pthread_mutex_unlock(&mutex); 

	if (ft_check_philo_states(bigdata) == DEAD)
		return (ft_free_all(bigdata));

	i = -1;
	while (++i < general.nb_of_philo)
	{
		if (pthread_join(bigdata[i].th, NULL) != 0) //attend que le thread soit termine pour quitter le programme
			return (ft_free_all(bigdata));
		printf("Thread %d has finished execution\n", bigdata[i].philo_nb);
	}
	ft_free_all(bigdata);
	return (0);
}
