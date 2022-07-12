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

void	*routine(void	*da)
{
	t_data	*data;
	int	is_dead;
	
	is_dead = 0;
	data = (t_data *)da;
//	printf("philo nb = %d\n", data->philo_nb);
	while (is_dead == 0)
	{
		if ((data->philo_nb)%2 == 0)
			usleep(1000);
		
		if (data->philo_nb == 1)
		{
			pthread_mutex_lock(&(data->tab_mut[(data->philo_nb) - 1]));	
			pthread_mutex_lock(&(data->tab_mut[(data->general->nb_of_philo) - 1]));
			printf("philo %d is eating", data->philo_nb);
			usleep((data->general->time_to_eat) * 1000);
			pthread_mutex_unlock(&(data->tab_mut[(data->philo_nb) - 1]));	
			pthread_mutex_unlock(&(data->tab_mut[(data->general->nb_of_philo) - 1]));
		}
		else if (data->philo_nb == data->general->nb_of_philo)
		{
			pthread_mutex_lock(&(data->tab_mut[(data->philo_nb) - 1]));	
			pthread_mutex_lock(&(data->tab_mut[0]));
			printf("philo %d is eating", data->philo_nb);
			usleep((data->general->time_to_eat) * 1000);
			pthread_mutex_unlock(&(data->tab_mut[(data->philo_nb) - 1]));	
			pthread_mutex_unlock(&(data->tab_mut[(data->general->nb_of_philo) - 1]));			
		}
		else
		{
			if ((data->philo_nb)%2 == 1)
			{
				pthread_mutex_lock(&(data->tab_mut[(data->philo_nb) - 1]));
				pthread_mutex_lock(&(data->tab_mut[data->philo_nb]));
				usleep((data->general->time_to_eat) * 1000);
				//printf()// nb de millisecondes en format depuis le lancement
				pthread_mutex_lock(&(data->tab_mut[(data->philo_nb) - 1]));
				pthread_mutex_unlock(&(data->general->mutex));
			}
			else if ((data->philo_nb)%2 == 0)
			{
				pthread_mutex_lock(&(data->tab_mut[data->philo_nb]));
				pthread_mutex_lock(&(data->tab_mut[(data->philo_nb) - 1]));
				printf("philo %d is eating", data->philo_nb);
				usleep((data->general->time_to_eat) * 1000);
				pthread_mutex_unlock(&(data->general->mutex));
				pthread_mutex_lock(&(data->tab_mut[(data->philo_nb) - 1]));
			}
		}
		
	}
	
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
	if (general.nb_of_philo == 0)
		return (0);
	data = ft_init_philo_structs(&general);
	if (!data)
		return (0);
	i = -1;
	while (++i < general.nb_of_philo)
		pthread_mutex_init(&data->tab_mut[i], NULL);
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
	i = -1;
	while (++i < general.nb_of_philo)
		pthread_mutex_destroy(&data->tab_mut[i]);
	//printf("Number of mails: %ld\n", mails);
	return (0);
}