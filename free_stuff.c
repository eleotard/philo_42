/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:06:47 by eleotard          #+#    #+#             */
/*   Updated: 2022/07/08 19:00:03 by eleotard         ###   ########.fr       */
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

int ft_free_all(t_philo *bigdata)
{
	int	i;

	i = -1;
	while (++i < bigdata->general->nb_of_philo)		
		pthread_mutex_destroy(&bigdata->tab_mut[i]);
	pthread_mutex_destroy(bigdata->mutex);
	free(bigdata->tab_mut);
	free(bigdata);
	return (-1);
}