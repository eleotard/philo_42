/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:06:42 by eleotard          #+#    #+#             */
/*   Updated: 2022/07/23 20:29:54 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*ft_init_mut_tab(t_general *general)
{
	int				i;
	pthread_mutex_t	*tab_mut;

	tab_mut = malloc(sizeof(pthread_mutex_t) * general->nb_of_philo);
	if (!tab_mut)
		return (NULL);
	i = -1;
	while (++i < general->nb_of_philo)
	{
		if (pthread_mutex_init(&tab_mut[i], NULL) != 0)
			return (free_destroy_tabmut(tab_mut, i));
	}
	return (tab_mut);
}

t_philo	*ft_init_philo_structs(t_general *general, t_mutex *mut, int *print)
{
	t_philo				*bigdata;
	t_philo				*philo;
	pthread_mutex_t		*tab_mut;
	int					i;

	tab_mut = ft_init_mut_tab(general);
	if (!tab_mut)
		return (ft_destroy_free_mutexs(mut));
	bigdata = malloc(sizeof(t_philo) * general->nb_of_philo);
	if (!bigdata)
		return (ft_destroy_all_mutexs(tab_mut, general->nb_of_philo, mut));
	philo = bigdata;
	i = -1;
	while (++i < general->nb_of_philo)
	{
		philo->tab_mut = tab_mut;
		philo->mut = mut;
		philo->print = print;
		philo->general = general;
		philo->philo_nb = i;
		philo->last_meal = 0;
		philo++;
	}
	return (bigdata);
}

t_mutex	*ft_init_mutex_struct(t_mutex *mut)
{
	pthread_mutex_t	*m_start;
	pthread_mutex_t	*can_print;
	pthread_mutex_t	*m_meal;

	m_start = malloc(sizeof(pthread_mutex_t));
	if (!m_start)
		return (NULL);
	can_print = malloc(sizeof(pthread_mutex_t));
	if (!can_print)
		return (free_rt_null_mut(m_start, NULL, NULL));
	m_meal = malloc(sizeof(pthread_mutex_t));
	if (!m_meal)
		return (free_rt_null_mut(m_start, can_print, NULL));
	if (pthread_mutex_init(m_start, NULL) != 0)
		return (free_rt_null_mut(m_start, NULL, NULL));
	if (pthread_mutex_init(can_print, NULL) != 0)
		return (ft_destroy_free_mutexs_2(m_start, can_print, NULL));
	if (pthread_mutex_init(m_meal, NULL) != 0)
		return (ft_destroy_free_mutexs_2(m_start, can_print, m_meal));
	mut->can_print = can_print;
	mut->m_meal = m_meal;
	mut->m_start = m_start;
	return (mut);
}

void	ft_attribute_philo_forks(t_philo *bigdata)
{
	t_philo	*philo;
	int		i;

	i = -1;
	philo = bigdata;
	while (++i < bigdata->general->nb_of_philo)
	{
		if (philo->philo_nb == 0) //donc le premier
		{
			philo->forks.f_fork = &philo->tab_mut[0];
			philo->forks.s_fork = &philo->tab_mut[1];
		}
		else if (philo->philo_nb == (bigdata->general->nb_of_philo - 1))
		{
			philo->forks.f_fork = &philo->tab_mut[0];
			philo->forks.s_fork = &philo->tab_mut[philo->philo_nb];
		}
		else //les autres
		{
			philo->forks.f_fork = &philo->tab_mut[philo->philo_nb];
			philo->forks.s_fork = &philo->tab_mut[(philo->philo_nb) + 1];
		}
		philo++;
	}
}

void	ft_init_general(t_general *general, int argc, char **argv)
{
	char	**tab;

	if (argc == 2)
	{
		tab = ft_split(argv[1], ' ');
		general->nb_of_philo = ft_atoi(tab[0]);
		general->time_to_die = ft_atoi(tab[1]);
		general->time_to_eat = ft_atoi(tab[2]);
		general->time_to_sleep = ft_atoi(tab[3]);
		general->nb_of_time = ft_atoi(tab[4]); // si ya que 4 ar, = 0, si 5 = arg 
		ft_free_tab(tab);
	}
	else
	{
		general->nb_of_philo = ft_atoi(argv[1]);
		general->time_to_die = ft_atoi(argv[2]);
		general->time_to_eat = ft_atoi(argv[3]);
		general->time_to_sleep = ft_atoi(argv[4]);
		general->nb_of_time = ft_atoi(argv[5]);
	}
}
