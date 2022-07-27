/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:09:52 by eleotard          #+#    #+#             */
/*   Updated: 2022/07/27 21:26:25 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_state_over_or_dead(t_philo *philo, int state)
{
	if (state == OVER)
		return (1);
	else if (state == DEAD)
	{
		pthread_mutex_lock(&philo->mut->can_print);
		*philo->print = 0;
		printf("%lld %d is dead\n", (ft_get_time() - philo->general->start),
			philo->philo_nb + 1);
		pthread_mutex_unlock(&philo->mut->can_print);
		return (1);
	}
	return (0);
}

t_philo	*ft_make_death_check(t_philo *bigdata, t_philo *philo, int *state)
{
	int	i;

	i = 0;
	while (i < bigdata->general->nb_of_philo)
	{
		pthread_mutex_lock(&philo->mut->m_meal);
		if ((ft_get_time() - philo->general->start - philo->last_meal
				> philo->general->time_to_die) && philo->state != OVER)
		{
			*state = DEAD;
			pthread_mutex_unlock(&philo->mut->m_meal);
			return (philo);
		}
		if (philo->state == OVER)
		{
			*state = OVER;
			pthread_mutex_unlock(&philo->mut->m_meal);
			return (philo);
		}
		pthread_mutex_unlock(&philo->mut->m_meal);
		philo++;
		i++;
	}
	return (philo);
}

void	ft_check_philo_states(t_philo *bigdata)
{
	int		state;
	t_philo	*philo;

	state = 0;
	while (1)
	{
		philo = bigdata;
		philo = ft_make_death_check(bigdata, philo, &state);
		if (ft_state_over_or_dead(philo, state))
			break ;
		usleep(8000);
	}
}
