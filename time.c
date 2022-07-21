/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 20:41:15 by eleotard          #+#    #+#             */
/*   Updated: 2022/07/21 20:41:49 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long long ft_get_time()
{
	struct timeval			current_time;
	unsigned long long		time;

	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

unsigned long long ft_get_time_micro()
{
	struct timeval			current_time;
	unsigned long long		time;

	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec *1000000) + (current_time.tv_usec);
	return (time);
}
