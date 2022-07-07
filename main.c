/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 02:19:03 by eleotard          #+#    #+#             */
/*   Updated: 2022/07/07 23:44:05 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int		mails = 0;
pthread_mutex_t	mutex;

void	*routine(void	*da)
{
	t_data	*data;

	data = (t_data *)da;

	//pthread_mutex_lock(&mutex);
	//printf("philo nb = %d\n", philo_nb);
	//pthread_mutex_unlock(&mutex);
	
	//printf("tte = %d\n", ti->time_to_die);
	printf("philo nb = %d\n", data->philo_nb);

	
	/*int	is_dead;
	int	is_eating;
	int	is_sleeping;
	
	is_dead = 0;
	is_eating = 0;
	is_sleeping = 0;

	while (is_dead == 0)
	{
		
	}*/
	
	/*long int	i;
	i = 0;
	while (i < 1000000)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
		i++;
	}*/
	return (NULL);
}

void	ft_init_time(t_time *time, char **argv)
{
	time->nb_of_philo = ft_atoi(argv[1]);
	time->time_to_die = ft_atoi(argv[2]);
	time->time_to_eat = ft_atoi(argv[3]);
	time->time_to_sleep = ft_atoi(argv[4]);
}

//void	ft_init_mut()

int	main(int argc, char **argv)
{
	//pthread_t	*th;	//tableau avec 4 structures dedans
	int			i;
	t_data		*data;
	t_data		*buff;
	t_time		time;
	pthread_mutex_t	mutex;
	int			*tab_mut;
	
	printf("OKKK\n");
	if (ft_check_parsing(argc, argv) == ERROR)
		return (0);
	
	pthread_mutex_init(&mutex, NULL);
	printf("OKKK 2\n");	
	ft_init_time(&time, argv);
	data = malloc(sizeof(t_data) * time.nb_of_philo);
	tab_mut = malloc(sizeof(int) * time.nb_of_philo);
	printf("OKKK 3\n");	
	i = -1;
	while (++i < time.nb_of_philo)
		tab_mut[i] = 1;
	printf("OKKK 4\n");	
	buff = data;
	i = 0;
	while (i < time.nb_of_philo)
	{
		buff->tab = tab_mut;
		buff->time = &time;
		buff->philo_nb = i + 1;
		i++;
		printf("bn = %d\n", buff->philo_nb);
		buff++;	
	}
	printf("AAA\n");

	i = 0;
	buff = data;
	while (i < time.nb_of_philo)
	{
		if (pthread_create(&buff->th, NULL, &routine, &buff)) //!= 0
			return (1);
		printf("Thread %d has started execution\n", buff->philo_nb);
		buff++;
		i++;
	}
	i = 0;
	buff = data;
	while (i < time.nb_of_philo)
	{
		if (pthread_join(buff->th, NULL) != 0) //attend que le thread soit termine pour quitter le programme
			return (2);
		printf("Thread %d has finished execution\n", buff->philo_nb);
		buff++;
		i++;
	}
	free(tab_mut);
	free(data);
	pthread_mutex_destroy(&mutex);
	//printf("Number of mails: %ld\n", mails);
	return (0);
}