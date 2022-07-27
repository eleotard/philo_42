/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 20:41:15 by eleotard          #+#    #+#             */
/*   Updated: 2022/07/27 14:48:43 by eleotard         ###   ########.fr       */
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

	start = ft_get_time_micro();
	curr_time = 0;
	ms = ms * 1000;
	while (curr_time <= ms)
	{
		pthread_mutex_lock(&philo->mut->can_print);
		if (*philo->print == 0)
		{
			pthread_mutex_unlock(&philo->mut->can_print);
			break ;
		}
		pthread_mutex_unlock(&philo->mut->can_print);
		curr_time = ft_get_time_micro() - start;
		if (ms - curr_time < 100)
			usleep((ms - curr_time) / 10);
		else
			usleep(100);
		curr_time = ft_get_time_micro() - start;
	}
}
