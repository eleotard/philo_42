/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 02:19:03 by eleotard          #+#    #+#             */
/*   Updated: 2022/07/27 14:42:39 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	ft_check_nb_of_meals(t_philo *philo, int meal)
{
	if (philo->general->nb_of_time != 0)
	{
		if (meal >= philo->general->nb_of_time)
		{
			pthread_mutex_lock(&philo->mut->m_meal);
			philo->state = OVER;
			pthread_mutex_unlock(&philo->mut->m_meal);
			return (OVER);
		}
	}
	return (0);
}

void	ft_mutex_starts_threads(t_philo *philo)
{
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
}

void	*routine(void	*da)
{
	t_philo		*philo;
	int			meal;

	philo = (t_philo *)da;
	ft_mutex_starts_threads(philo);
	if (ft_check_thread_error_in_routine(philo) == ERROR)
		return (NULL);
	if (((philo->general->nb_of_philo) % 2 == 0)
		&& (((philo->philo_nb + 1) % 2) == 0))
		ft_myusleep(philo, philo->general->time_to_eat / 10);
	else if (((philo->general->nb_of_philo) % 2 == 1)
		&& (((philo->philo_nb + 1) % 2) == 1))
		ft_myusleep(philo, philo->general->time_to_eat / 10);
	meal = 0;
	while (ft_check_print(philo) == 0)
	{
		if (ft_eat(philo))
			meal++;
		if (ft_check_nb_of_meals(philo, meal) == OVER
			|| philo->general->nb_of_philo == 1)
			break ;
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
