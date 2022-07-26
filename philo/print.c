/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:52:01 by eleotard          #+#    #+#             */
/*   Updated: 2022/07/26 16:52:38 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_output(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->mut->can_print);
	if (*philo->print == 1)
	{
		printf("%lld %d %s", (ft_get_time() - philo->general->start),
			philo->philo_nb + 1, str);
	}
	pthread_mutex_unlock(&philo->mut->can_print);
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
