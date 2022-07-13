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
  //printf("seconds : %ld\nmicro seconds : %ld", current_time.tv_sec, current_time.tv_usec);
	//printf("time ds ft = %ld\n", time);
	return (time);
}


void	*routine(void	*da)
{
	t_philo		*philo;
	int			is_dead;
	long int	start;
	//long int	time_death;
	
	philo = (t_philo *)da;

	pthread_mutex_lock(philo->mutex);
	start = philo->general->start;
	pthread_mutex_unlock(philo->mutex);
	//printf("start = %ld\n", start);
	is_dead = 0;

	//printf("philo nb = %d\n", philo->philo_nb);
	while (is_dead == 0)
	{
		//time_death = ft_get_time() + data->general->time_to_die;
		
		if ((philo->philo_nb)%2 == 1)
			usleep(1000);
		
		pthread_mutex_lock(philo->forks.l_fork);
		pthread_mutex_lock(philo->forks.r_fork);
		printf("%ld\t %d has taken a fork\n", (ft_get_time() - start), philo->philo_nb);
		printf("%ld\t %d has taken a fork\n", (ft_get_time() - start), philo->philo_nb);
		printf("%ld\t %d is eating\n", (ft_get_time() - start), philo->philo_nb);
		usleep((philo->general->time_to_eat) * 1000);
		printf("%ld\t %d has let down a fork\n", (ft_get_time() - start), philo->philo_nb);
		printf("%ld\t %d has let down a fork\n", (ft_get_time() - start), philo->philo_nb);
		pthread_mutex_unlock(philo->forks.l_fork);
		pthread_mutex_unlock(philo->forks.r_fork);
		printf("%ld\t %d is sleeping\n", (ft_get_time() - start), philo->philo_nb);
		usleep((philo->general->time_to_sleep) * 1000);
	
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

int	main(int argc, char **argv)
{
	int				i;
	t_philo			*bigdata;
	t_general		general;
	pthread_mutex_t	mutex;

	
	if (ft_check_parsing(argc, argv) == ERROR)
		return (0);

	//mutex = malloc(sizeof(pthread_mutex_t) * 1);
	if (pthread_mutex_init(&mutex, NULL) != 0)
		return (-1);
	ft_init_general(&general, argc, argv);
	bigdata = ft_init_philo_structs(&general, &mutex);
	if (!bigdata)
		return (-1);
	ft_init_philo_forks(bigdata);

	i = -1;
	pthread_mutex_lock(&mutex);
	while (++i < general.nb_of_philo)
	{
		if (pthread_create(&bigdata[i].th, NULL, &routine, &bigdata[i])) //!= 0
			return (1);
		printf("Thread %d has started execution\n", bigdata[i].philo_nb);
	}
	general.start = ft_get_time();
	pthread_mutex_unlock(&mutex); 

	i = -1;
	while (++i < general.nb_of_philo)
	{
		if (pthread_join(bigdata[i].th, NULL) != 0) //attend que le thread soit termine pour quitter le programme
			return (2);
		printf("Thread %d has finished execution\n", bigdata[i].philo_nb);
	}
	i = -1;
	while (++i < general.nb_of_philo)
	{
		pthread_mutex_destroy(&bigdata->tab_mut[i]);
	}
	pthread_mutex_destroy(&mutex);
	free(bigdata->tab_mut);
	free(bigdata);
	return (0);
}
