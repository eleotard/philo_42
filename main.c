/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 02:19:03 by eleotard          #+#    #+#             */
/*   Updated: 2022/07/24 23:51:50 by eleotard         ###   ########.fr       */
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

int	ft_check_thread_error_in_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->mut->can_print);
	if (*philo->print == 0)
	{
		pthread_mutex_unlock(&philo->mut->can_print);
		return (ERROR);
	}
	pthread_mutex_unlock(&philo->mut->can_print);
	return (0);
}

void	*routine(void	*da)
{
	t_philo		*philo;

	philo = (t_philo *)da;
	if (((philo->philo_nb + 1) % 2) == 0)
	{
		pthread_mutex_lock(&philo->mut->m_start);
		pthread_mutex_unlock(&philo->mut->m_start);
	}
	else
	{
		pthread_mutex_lock(&philo->mut->m_start_2);
		pthread_mutex_unlock(&philo->mut->m_start_2);
	}
	if (ft_check_thread_error_in_routine(philo) == ERROR)
		return (NULL);
	if (((philo->general->nb_of_philo) % 2 == 0)
		&& (((philo->philo_nb + 1) % 2) == 0))
		ft_myusleep(philo, (philo->general->time_to_eat / 10));
	while (ft_check_print(philo) == 0)
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}	
	return (NULL);
}

int	main(int argc, char **argv)
{
	int				print;
	t_philo			*bigdata;
	t_general		general;
	t_mutex			i_mut;

	print = 1;
	if (ft_check_parsing(argc, argv) == ERROR)
		return (-1);
	ft_init_general(&general, argc, argv);
	if (ft_check_correct_input(argc, argv, &general) == ERROR)
		return (-1);
	if (ft_init_mutex_struct(&i_mut) == ERROR)
		return (-1);
	bigdata = ft_init_philo_structs(&general, &i_mut, &print);
	if (!bigdata)
		return (-1);
	ft_attribute_philo_forks(bigdata);
	if (ft_create_threads(bigdata) == ERROR)
		return (-1);
	ft_check_philo_states(bigdata);
	if (ft_join_threads(bigdata) == ERROR)
		return (-1);
	ft_free_all(bigdata);
	return (0);
}
