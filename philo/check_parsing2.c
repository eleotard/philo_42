/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 18:07:00 by eleotard          #+#    #+#             */
/*   Updated: 2022/07/28 19:17:00 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_arg(int argc, char **argv)
{
	if (argc == 2)
	{
		if (ft_check_arg_2(argv) == ERROR)
			return (ERROR);
	}
	else if (argc == 5)
	{
		if (ft_check_arg_5(argv) == ERROR)
			return (ERROR);
	}
	else if (argc == 6)
	{
		if (ft_check_arg_6(argv) == ERROR)
			return (ERROR);
	}
	else
		return (ERROR);
	return (0);
}

int	ft_check_arg_2(char **argv)
{
	int		k;
	char	**tab;

	k = 0;
	tab = ft_split(argv[1], ' ');
	if (!tab)
		return (ERROR);
	while (tab[k])
		k++;
	ft_free_tab(tab);
	if (k != 4 && k != 5)
		return (ERROR);
	return (0);
}

int	ft_check_arg_5(char **argv)
{
	int		k;
	int		i;
	char	**tab;

	i = 0;
	while (argv[++i])
	{
		k = 0;
		tab = ft_split(argv[i], ' ');
		if (!tab)
			return (ERROR);
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
	int		k;
	int		i;
	char	**tab;

	i = 0;
	while (argv[++i])
	{
		k = 0;
		tab = ft_split(argv[i], ' ');
		if (!tab)
			return (ERROR);
		while (tab[k])
			k++;
		ft_free_tab(tab);
		if (k != 1)
			return (ERROR);
	}
	return (0);
}
