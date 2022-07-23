/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:06:47 by eleotard          #+#    #+#             */
/*   Updated: 2022/07/23 20:29:20 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	**ft_free_tab(char **tab)
{
	int	k;

	k = 0;
	while (tab[k])
		k++;
	while (k >= 0)
	{
		free(tab[k]);
		k--;
	}
	free(tab);
	return (NULL);
}

t_philo	*free_rt_null(t_philo *data)
{
	free(data);
	return(NULL);
}

void	*free_rt_null_mut(pthread_mutex_t *m_start, pthread_mutex_t *can_print, pthread_mutex_t *m_meal, pthread_mutex_t *m_start_2)
{
	if (m_start)
		free (m_start);
	if (can_print)
		free(can_print);
	if (m_meal)
		free (m_meal);
	if (m_start_2)
		free (m_start_2);
	return (NULL);
}

int ft_free_all(t_philo *bigdata)
{
	int	i;

	i = -1;
	pthread_mutex_lock(bigdata->mut->m_start);
	while (++i < bigdata->general->nb_of_philo)		
		pthread_mutex_destroy(&bigdata->tab_mut[i]);
	pthread_mutex_unlock(bigdata->mut->m_start);
	free(bigdata->tab_mut);
	ft_destroy_free_mutexs(bigdata->mut);
	free(bigdata);
	return (-1);
}
