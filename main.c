/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 02:19:03 by eleotard          #+#    #+#             */
/*   Updated: 2022/07/08 23:05:54 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int		mails = 0;
pthread_mutex_t	mutex;

void	*routine(void	*da)
{
	t_data	*data;
	/*int	is_dead;
	int	is_eating;
	int	is_sleeping;
	
	is_dead = 0;
	is_eating = 0;
	is_sleeping = 0;*/
	data = (t_data *)da;
	printf("philo nb = %d\n", data->philo_nb);
	
	//pthread_mutex_lock(&mutex);
	//pthread_mutex_unlock(&mutex);

	/*while (is_dead == 0)
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
		ft_free_tab(tab);
	}
	else
	{
		general->nb_of_philo = ft_atoi(argv[1]);
		general->time_to_die = ft_atoi(argv[2]);
		general->time_to_eat = ft_atoi(argv[3]);
		general->time_to_sleep = ft_atoi(argv[4]);
	}
}

t_data	*ft_init_philo_structs(t_general *general)
{
	t_data		*data;
	t_data		*buff;
	int			*tab_mut;
	int			i;
	
	data = malloc(sizeof(t_data) * general->nb_of_philo);
	if (!data)
		return (NULL);
	tab_mut = malloc(sizeof(int) * general->nb_of_philo);
	if (!tab_mut)
		return (free_rt_null(data));
	i = -1;
	while (++i < general->nb_of_philo)
		tab_mut[i] = 1;
	buff = data;
	i = -1;
	while (++i < general->nb_of_philo)
	{
		buff->tab_mut = tab_mut;
		buff->general = general;
		buff->philo_nb = i + 1;
		buff++;	
	}
	return (data);
}

int	main(int argc, char **argv)
{
	//pthread_t	*th;	//tableau avec 4 structures dedans
	int			i;
	t_data		*data;
	t_general	general;
	pthread_mutex_t	mutex;

	
	if (ft_check_parsing(argc, argv) == ERROR)
		return (0);
	
	pthread_mutex_init(&mutex, NULL);	
	ft_init_general(&general, argc, argv);
	data = ft_init_philo_structs(&general);
	if (!data)
		return (0);
	i = -1;
	while (++i < general.nb_of_philo)
	{
		if (pthread_create(&data[i].th, NULL, &routine, &data[i])) //!= 0
			return (1);
		printf("Thread %d has started execution\n", data[i].philo_nb);
	}
	i = -1;
	while (++i < general.nb_of_philo)
	{
		if (pthread_join(data[i].th, NULL) != 0) //attend que le thread soit termine pour quitter le programme
			return (2);
		printf("Thread %d has finished execution\n", data[i].philo_nb);
	}
	free(data->tab_mut);
	free(data);
	pthread_mutex_destroy(&mutex);
	//printf("Number of mails: %ld\n", mails);
	return (0);
}