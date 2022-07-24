/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 02:19:03 by eleotard          #+#    #+#             */
/*   Updated: 2022/07/24 19:05:40 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*void	ft_sleep(t_philo *philo, unsigned long long ms)
{
	unsigned long long	curr_time;
	unsigned long long	start_time;
	
	curr_time = ft_get_time() - philo->general->start;
	start_time = curr_time;
	//printf("\t\t\tcur time %lld\n", curr_time);
	while ((curr_time - start_time) <= ms)
	{
		usleep(100);
		curr_time = ft_get_time() - philo->general->start;
	}
}*/

/*void	ft_sleep2(unsigned long long ms)
{
	unsigned long long	curr_time;
	unsigned long long	end_time;

	curr_time = ft_get_time() - philo->general->start;
	end_time = curr_time + ms;
	while (1)
	{
		curr_time = ft_get_time();
		if(curr_time >= end_time)
			break;
		usleep(100);
	}
}*/


/*void	ft_myusleep(t_philo *philo, unsigned long long ms)
{
	unsigned long long	curr_time;
	unsigned long long	start;

	unsigned long long temps_debut = ft_get_time();
	start = ft_get_time_micro();
	ms = ms * 1000;
	
	while (1)
	{
		curr_time = (ft_get_time_micro() - start);
		if (curr_time >= ms)
			break ;
		if (ms - curr_time <= 100) //ms
			usleep((ms - curr_time));
		else
			usleep(100);
		curr_time = ft_get_time_micro() - start;
	}
	unsigned long long temps_fin = ft_get_time();
	printf("\t\t ms: [%lld] , temps attendu : [%lld]  philo[%d] \n", ms, temps_fin - temps_debut,  philo->philo_nb);
	fflush(stdout);
}*/

/*void	ft_myusleep(t_philo *philo, unsigned long long ms)
{
	int nb;
	
	unsigned long long temps_debut = ft_get_time();
	//printf("\t\tcurr time before %lld philo nb %d\n", curr_time, philo->philo_nb);
	//fflush(stdout);

	unsigned long long curr_time;
	

	nb = (ms * 1000) / 100;
	while (nb > 0)
	{
		curr_time = ft_get_time() - temps_debut;
		if (curr_time >= ms)
			break;
		usleep(100);
		nb--;
	}
	unsigned long long temps_fin = ft_get_time();
	printf("\t\t ms: [%lld] , temps attendu : [%lld]  philo[%d] \n", ms, temps_fin - temps_debut,  philo->philo_nb);
	fflush(stdout);
	
}*/


void	ft_print_output(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->mut->can_print);
	if (*philo->print == 1)
	{
		printf("%lld %d %s", (ft_get_time() - philo->general->start), philo->philo_nb + 1, str);
	}
	pthread_mutex_unlock(&philo->mut->can_print);
}

void	ft_myusleep(t_philo *philo, unsigned long long ms)
{
	unsigned long long	curr_time;
	unsigned long long	start;

	start = ft_get_time_micro();
	curr_time = 0;
	ms = ms * 1000;

	unsigned long long temps_debut = ft_get_time();
	while (curr_time <= ms)
	{
		curr_time = ft_get_time_micro() - start;
		if (ms - curr_time < 100)
			usleep((ms - curr_time) /10);
		else
			usleep(100);
		curr_time = ft_get_time_micro() - start;
	}
	unsigned long long temps_fin = ft_get_time();
	//printf("\t\t ms: [%lld] , temps attendu : [%lld]  philo[%d] \n", ms, temps_fin - temps_debut,  philo->philo_nb);
	//fflush(stdout);
}

int	ft_check_print(t_philo *philo)
{
	pthread_mutex_lock(&philo->mut->can_print);
	if (*philo->print == 0)
	{
		pthread_mutex_unlock(&philo->mut->can_print);
		return (1);
	}
	pthread_mutex_unlock(&philo->mut->can_print);
	return (0);
}

void	*routine(void	*da)
{
	t_philo		*philo;
	
	philo = (t_philo *)da;
	if (((philo->philo_nb + 1) % 2) == 0)
	{
		pthread_mutex_lock(&philo->mut->m_start);
		pthread_mutex_unlock(&philo->mut->m_start);
	}
	else
	{
		pthread_mutex_lock(&philo->mut->m_start_2);
		pthread_mutex_unlock(&philo->mut->m_start_2);
	}
	
	if (((philo->general->nb_of_philo) % 2 == 0) && (((philo->philo_nb + 1) % 2) == 0))
		ft_myusleep(philo, (philo->general->time_to_eat / 10));
	while (ft_check_print(philo) == 0)
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}	
	return (NULL);
}



int	main(int argc, char **argv)
{
	int				i;
	int				print;
	t_philo			*bigdata;
	t_general		general;
	t_mutex			i_mut;


	print = 1;
	if (ft_check_parsing(argc, argv) == ERROR)
		return (0);
	ft_init_general(&general, argc, argv);
	if (ft_check_correct_input(argc, argv, &general) == ERROR)
		return (-1);
	if (ft_init_mutex_struct(&i_mut) == ERROR)
		return (-1);
	bigdata = ft_init_philo_structs(&general, &i_mut, &print);
	if (!bigdata)
		return (-1);
	ft_attribute_philo_forks(bigdata);
	

	
	i = -1;
	pthread_mutex_lock(&bigdata->mut->m_start_2);
	pthread_mutex_lock(&bigdata->mut->m_start);
	while (++i < general.nb_of_philo)
	{
		if (pthread_create(&bigdata[i].th, NULL, &routine, &bigdata[i])) //!= 0
			return (ft_free_all(bigdata)); //attention c'est pas si simple malheureusement //destroy qd mm
		printf("Thread %d has started execution\n", bigdata[i].philo_nb + 1);
	}
	general.start = ft_get_time();
	pthread_mutex_unlock(&bigdata->mut->m_start);
	pthread_mutex_unlock(&bigdata->mut->m_start_2); 



	ft_check_philo_states(bigdata);




	i = -1;
	while (++i < general.nb_of_philo)
	{
		if (pthread_join(bigdata[i].th, NULL) != 0) //attend que le thread soit termine pour quitter le programme
			return (ft_free_all(bigdata));
		printf("Thread %d has finished execution\n", bigdata[i].philo_nb + 1);
	}
	ft_free_all(bigdata);
	return (0);
}
