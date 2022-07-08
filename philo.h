/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:24:47 by eleotard          #+#    #+#             */
/*   Updated: 2022/07/08 19:08:59 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <stddef.h>
# include <pthread.h>
# include <sys/time.h>

# include "libft/libft.h"

# define ERROR -1

typedef struct s_general
{
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nb_of_philo;
}	t_general;

typedef struct s_data
{
	pthread_t	th;
	int			*tab_mut;
	char		*argv;
	t_general	*general;
	int			philo_nb;
}	t_data;

typedef struct s_lst
{
	int		content;
	void	*next;
}	t_lst;

typedef struct s_rdm
{
	int		i;
	int		j;
	int		k;
	char	**tab;
}	t_rdm;

/*PARSING*/
int	ft_check_parsing(int argc, char **argv);
int	ft_check_correct_caracters(char **argv);
int	ft_check_is_digit(t_rdm *va);
int	ft_check_correct_int(char **argv);
int	ft_check_overflow(char **argv);
int	ft_atoi_max(const char *nptr);
int	ft_previous_check(int *sign, const char *nptr);

/*FREE*/
char	**ft_free_tab(char **tab);
t_data	*free_rt_null(t_data *data);

#endif