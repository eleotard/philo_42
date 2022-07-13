/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 18:07:00 by eleotard          #+#    #+#             */
/*   Updated: 2022/07/09 18:07:26 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_arg_2(char **argv)
{
	int		k;
	char **tab;

	k = 0;
	tab = ft_split(argv[1], ' ');
	while (tab[k])
		k++;
	ft_free_tab(tab);
	if (k != 4 && k != 5)
		return (ERROR);
	return (0);
}

int	ft_check_arg_5(char **argv)
{
	int	k;
	int	i;
	char **tab;

	i = -1;
	k = 0;
	while (argv[++i])
	{
		tab = ft_split(argv[i], ' ');
		while (tab[k])
			k++;
		ft_free_tab(tab);
		if (k != 1)
			return (ERROR);
	}
	return (0);
}

int	ft_check_arg_6(char **argv)
{
	int	k;
	int	i;
	char **tab;

	i = -1;
	k = 0;
	while (argv[++i])
	{
		tab = ft_split(argv[i], ' ');
		while (tab[k])
			k++;
		ft_free_tab(tab);
		if (k != 1)
			return (ERROR);
	}
	return (0);
}

int	ft_check_correct_input(int argc, char **argv, t_general *general)
{
	if (general->nb_of_philo == 0 || general->nb_of_philo == 1)
		return (ERROR);
	if (argc == 6 && general->nb_of_time == 0)
		return (ERROR);
	else if (argc == 2 && ft_find_nb_of_arg(argv[1]) == 5 && general->nb_of_time == 0)
		return (ERROR);
	return (0);
}