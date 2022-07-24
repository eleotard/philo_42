/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:09:52 by eleotard          #+#    #+#             */
/*   Updated: 2022/07/24 19:13:45 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_check_philo_states(t_philo *bigdata)
{
	int		i;
	t_philo *philo;
	int 	state;

	state = 0;
	while (1)
	{
		i = -1;
		philo = bigdata;
		while (++i < bigdata->general->nb_of_philo)
		{
			pthread_mutex_lock(&philo->mut->m_meal);
			if (ft_get_time() - philo->general->start - philo->last_meal
				> philo->general->time_to_die)
			{
				//printf("checher ; %lld\n", ft_get_time() - philo->general->start - philo->last_meal);
				state = DEAD;
				pthread_mutex_unlock(&philo->mut->m_meal);
				break ;
			}
			pthread_mutex_unlock(&philo->mut->m_meal);
			philo++;
		}
		if (state == DEAD)
		{
			pthread_mutex_lock(&philo->mut->can_print);
			*philo->print = 0;
			printf("%lld %d is dead\n", (ft_get_time() - philo->general->start)
				,philo->philo_nb + 1);
			pthread_mutex_unlock(&philo->mut->can_print);
			break ;
		}
		usleep(8000);
	}
}