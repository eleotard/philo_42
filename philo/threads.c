/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 22:43:51 by eleotard          #+#    #+#             */
/*   Updated: 2022/07/26 21:18:00 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_create_threads(t_philo *bigdata)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&bigdata->mut->m_start_2);
	pthread_mutex_lock(&bigdata->mut->m_start);
	while (++i < bigdata->general->nb_of_philo)
	{
		if (pthread_create(&bigdata[i].th, NULL, &routine, &bigdata[i]))
			return (ft_deal_with_ptc(bigdata, i));
	}
	bigdata->general->start = ft_get_time();
	pthread_mutex_unlock(&bigdata->mut->m_start);
	pthread_mutex_unlock(&bigdata->mut->m_start_2);
	return (0);
}

int	ft_join_threads(t_philo *bigdata)
{
	int	i;

	i = -1;
	while (++i < bigdata->general->nb_of_philo)
	{
		if (pthread_join(bigdata[i].th, NULL) != 0)
			return (ft_deal_with_ptj(bigdata));
	}
	return (0);
}
