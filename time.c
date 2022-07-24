/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 20:41:15 by eleotard          #+#    #+#             */
/*   Updated: 2022/07/24 23:38:40 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long long	ft_get_time(void)
{
	struct timeval			current_time;
	unsigned long long		time;

	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

unsigned long long	ft_get_time_micro(void)
{
	struct timeval			current_time;
	unsigned long long		time;

	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec * 1000000) + (current_time.tv_usec);
	return (time);
}

void	ft_myusleep(t_philo *philo, unsigned long long ms)
{
	unsigned long long	curr_time;
	unsigned long long	start;
	unsigned long long	temps_debut;
	unsigned long long	temps_fin;

	start = ft_get_time_micro();
	curr_time = 0;
	ms = ms * 1000;
	temps_debut = ft_get_time();
	while (curr_time <= ms)
	{
		curr_time = ft_get_time_micro() - start;
		if (ms - curr_time < 100)
			usleep((ms - curr_time) / 10); //a voir
		else
			usleep(100);
		curr_time = ft_get_time_micro() - start;
	}
	temps_fin = ft_get_time();
	//printf("\t\t ms: [%lld] , temps attendu : [%lld]  philo[%d] \n", ms, temps_fin - temps_debut,  philo->philo_nb);
}
