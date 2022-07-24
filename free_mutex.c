/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:06:47 by eleotard          #+#    #+#             */
/*   Updated: 2022/07/24 19:14:47 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_destroy_mutexs(t_mutex *mut)
{
	pthread_mutex_destroy(&mut->can_print);
	pthread_mutex_destroy(&mut->m_start);
	pthread_mutex_destroy(&mut->m_meal);
	pthread_mutex_destroy(&mut->m_start_2);
	return (NULL);
}

void	*ft_destroy_mutexs_2(pthread_mutex_t *m_start, pthread_mutex_t *can_print, pthread_mutex_t *m_meal, pthread_mutex_t *m_start_2)
{
	if (can_print)
		pthread_mutex_destroy(m_start);
	if (m_meal)
		pthread_mutex_destroy(can_print);
	if (m_start_2)
		pthread_mutex_destroy(m_meal);
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
	ft_destroy_mutexs(mut);
	return (NULL);
}