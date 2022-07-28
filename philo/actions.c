/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:54:55 by eleotard          #+#    #+#             */
/*   Updated: 2022/07/29 00:57:33 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->forks.f_fork);
	ft_print_output(philo, "has taken a fork\n");
	if (philo->forks.s_fork == NULL)
	{
		pthread_mutex_unlock(philo->forks.f_fork);
		return (0);
	}
	else
	{
		pthread_mutex_lock(philo->forks.s_fork);
		ft_print_output(philo, "has taken a fork\n");
	}
	pthread_mutex_lock(&philo->mut->m_meal);
	philo->last_meal = (ft_get_time() - philo->general->start);
	pthread_mutex_unlock(&philo->mut->m_meal);
	ft_print_output(philo, "is eating\n");
	ft_myusleep(philo, philo->general->time_to_eat);
	pthread_mutex_unlock(philo->forks.f_fork);
	pthread_mutex_unlock(philo->forks.s_fork);
	return (1);
}

void	ft_sleep(t_philo *philo)
{
	ft_print_output(philo, "is sleeping\n");
	ft_myusleep(philo, philo->general->time_to_sleep);
}

void	ft_think(t_philo *philo)
{
	unsigned long long	time_to_think;

	if (((philo->general->nb_of_philo) % 2) == 0)
		ft_print_output(philo, "is thinking\n");
	else
	{
		time_to_think = 1 * (philo->general->time_to_eat);
		ft_print_output(philo, "is thinking\n");
		ft_myusleep(philo, time_to_think);
	}
}
