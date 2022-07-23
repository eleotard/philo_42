/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:06:47 by eleotard          #+#    #+#             */
/*   Updated: 2022/07/23 20:29:20 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_destroy_free_mutexs(t_mutex *mut)
{
	pthread_mutex_destroy(mut->can_print);
	pthread_mutex_destroy(mut->m_start);
	pthread_mutex_destroy(mut->m_meal);
	pthread_mutex_destroy(mut->m_start_2);
	free(mut->can_print);
	free(mut->m_meal);
	free(mut->m_start);
	free(mut->m_start_2);
	return (NULL);
}

void	*ft_destroy_free_mutexs_2(pthread_mutex_t *m_start, pthread_mutex_t *can_print, pthread_mutex_t *m_meal, pthread_mutex_t *m_start_2)
{
	if (m_start)
	{
		free(m_start);
	}
	if (can_print)
	{
		pthread_mutex_destroy(m_start);
		free(can_print);
	}
	if (m_meal)
	{
		pthread_mutex_destroy(can_print);
		free(m_meal);
	}
		if (m_start_2)
	{
		pthread_mutex_destroy(m_meal);
		free(m_start_2);
	}
	return (NULL);
}

void	*free_destroy_tabmut(pthread_mutex_t *tab_mut, int k)
{
	k--;
	while (k >= 0)
	{
		pthread_mutex_destroy(&tab_mut[k]);
		k--;
	}
	free (tab_mut);
	return (NULL);
}

void	*ft_destroy_all_mutexs(pthread_mutex_t *tab_mut, int k, t_mutex *mut)
{
	free_destroy_tabmut(tab_mut, k);
	ft_destroy_free_mutexs(mut);
	return (NULL);
}