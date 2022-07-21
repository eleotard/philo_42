/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:54:55 by eleotard          #+#    #+#             */
/*   Updated: 2022/07/21 20:22:08 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->forks.f_fork);
	ft_print_output(philo, "has taken a fork\n");
	pthread_mutex_lock(philo->forks.s_fork);
	ft_print_output(philo, "has taken a fork\n");
	pthread_mutex_lock(philo->mut->m_meal);
	philo->last_meal = (ft_get_time() - philo->general->start);
	//printf("\n\n\t\tphilo %d last meal = %lld\n\n", philo->philo_nb + 1, philo->last_meal);
	pthread_mutex_unlock(philo->mut->m_meal);
	ft_print_output(philo, "is eating\n");
	ft_myusleep(philo, philo->general->time_to_eat);
	//ft_sleep(philo, philo->general->time_to_eat);
	pthread_mutex_unlock(philo->forks.f_fork);
	pthread_mutex_unlock(philo->forks.s_fork);
}

void	ft_sleep(t_philo *philo)
{
	ft_print_output(philo, "is sleeping\n");
	ft_myusleep(philo, philo->general->time_to_sleep);
}