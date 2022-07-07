/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:24:47 by eleotard          #+#    #+#             */
/*   Updated: 2022/07/07 23:22:21 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <stddef.h>
# include <pthread.h>

# include "libft/libft.h"

# define ERROR -1

typedef struct s_time
{
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nb_of_philo;
}	t_time;

typedef struct s_data
{
	pthread_t	th;
	int			*tab;
	char		*argv;
	t_time		*time;
	int			philo_nb;
}	t_data;

typedef struct s_lst
{
	int		content;
	void	*next;
}	t_lst;


/*PARSING*/
int	ft_check_parsing(int argc, char **argv);
int	ft_check_correct_caracters(char **argv);
int	ft_check_is_digit(t_data *va);
int	ft_check_correct_int(char **argv);
int	ft_check_overflow(char **argv);
int	ft_atoi_max(const char *nptr);
int	ft_previous_check(int *sign, const char *nptr);

/*FREE*/
char	**ft_free_tab(char **tab);

#endif