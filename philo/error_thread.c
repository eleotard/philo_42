/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 22:33:14 by eleotard          #+#    #+#             */
/*   Updated: 2022/07/24 23:39:08 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_deal_with_ptc(t_philo *bigdata, int i)
{
	pthread_mutex_lock(&bigdata->mut->can_print);
	*bigdata->print = 0;
	pthread_mutex_unlock(&bigdata->mut->can_print);
	pthread_mutex_unlock(&bigdata->mut->m_start);
	pthread_mutex_unlock(&bigdata->mut->m_start_2);
	while (--i >= 0)
	{
		if (pthread_join(bigdata[i].th, NULL) != 0)
			return (ft_deal_with_ptj(bigdata));
		printf("Thread %d has finished execution\n", bigdata[i].philo_nb + 1);
	}
	ft_free_all(bigdata);
	return (-1);
}

int	ft_deal_with_ptj(t_philo *bigdata)
{
	pthread_mutex_lock(&bigdata->mut->can_print);
	*bigdata->print = 0;
	pthread_mutex_unlock(&bigdata->mut->can_print);
	usleep(1000000);
	ft_free_all(bigdata);
	return (-1);
}
