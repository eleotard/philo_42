/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 18:51:40 by eleotard          #+#    #+#             */
/*   Updated: 2022/07/09 18:07:49 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_parsing(int argc, char **argv)
{
	if (argc <= 1)
		return (ERROR);
	if (ft_check_arg(argc, argv) == ERROR
		|| ft_check_correct_caracters(argv) == ERROR
		|| ft_check_correct_int(argv) == ERROR
		|| ft_check_overflow(argv) == ERROR)
	{
		ft_putstr_fd("Error\n", 2);
		return (ERROR);
	}
	return (0);
}

int ft_check_arg(int argc, char **argv)
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

int	ft_check_correct_caracters(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		while (argv[i][j])
		{
			if (argv[i][j] != '+'
				&& (argv[i][j] < '0' || argv[i][j] > '9')
				&& argv[i][j] != ' ')
				return (ERROR);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

int	ft_check_is_digit(t_rdm *va)
{
	if ((va->tab[va->k][0] == '+') && (va->tab[va->k][1] != '\0'))
		va->j++;
	while (va->tab[va->k][va->j])
	{
		if (va->tab[va->k][va->j] < '0' || va->tab[va->k][va->j] > '9')
		{
			va->tab = ft_free_tab(va->tab);
			return (ERROR);
		}
		va->j++;
	}
	return (0);
}

int	ft_check_correct_int(char **argv)
{
	t_rdm	va;

	va.i = 0;
	va.j = 0;
	va.k = -1;
	while (argv[++va.i])
	{
		va.tab = ft_split(argv[va.i], ' ');
		if (!va.tab)
			return (ERROR);
		if (va.tab[0] == NULL)
		{
			va.tab = ft_free_tab(va.tab);
			return (ERROR);
		}
		while (va.tab[++va.k])
		{
			if (ft_check_is_digit(&va) == ERROR)
				return (ERROR);
			va.j = 0;
		}
		va.tab = ft_free_tab(va.tab);
		va.k = -1;
	}
	return (0);
}

int	ft_check_overflow(char **argv)
{
	t_rdm	va;

	va.i = 1;
	va.j = 0;
	va.k = 0;
	while (argv[va.i])
	{
		va.tab = ft_split(argv[va.i], ' ');
		if (!va.tab)
			return (ERROR);
		while (va.tab[va.k])
		{
			if (ft_atoi_max(va.tab[va.k]) == ERROR)
			{
				va.tab = ft_free_tab(va.tab);
				return (ERROR);
			}
			va.k++;
		}
		va.tab = ft_free_tab(va.tab);
		va.k = 0;
		va.i++;
	}
	return (0);
}
