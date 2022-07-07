/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_max.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:59:49 by eleotard          #+#    #+#             */
/*   Updated: 2022/07/04 17:26:29 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_previous_check(int *sign, const char *nptr)
{
	int	i;

	i = 0;
	while (nptr[i] == '\v' || nptr[i] == '\f' || nptr[i] == '\r'
		|| nptr[i] == '\t' || nptr[i] == '\n' || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			*sign = -1;
		i++;
	}
	return (i);
}

int	ft_atoi_max(const char *nptr)
{
	int			i;
	long int	result;
	int			sign;

	i = 0;
	result = 0;
	sign = 1;
	i = ft_previous_check(&sign, nptr);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (result > 2147483647 || result * -1 < -2147483648)
			break ;
		result = result * 10 + (nptr[i] - 48);
		i++;
	}
	if ((sign * result) > 2147483647 || (sign * result) < -2147483648)
		return (ERROR);
	else
		return (0);
}
