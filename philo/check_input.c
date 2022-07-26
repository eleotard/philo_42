/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 23:41:08 by eleotard          #+#    #+#             */
/*   Updated: 2022/07/26 16:12:40 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_correct_input(int argc, char **argv, t_general *general)
{
	if (general->nb_of_philo == 0 || general->nb_of_philo == 1
		|| general->nb_of_philo > 200)
		return (ERROR);
	if (general->time_to_eat < 60 || general->time_to_die < 60
		|| general->time_to_sleep < 60)
		return (ERROR);
	if (argc == 6 && general->nb_of_time == 0)
		return (ERROR);
	else if (argc == 2 && ft_find_nb_of_arg(argv[1]) == 5
		&& general->nb_of_time == 0)
		return (ERROR);
	return (0);
}
