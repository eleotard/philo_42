/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 17:16:21 by eleotard          #+#    #+#             */
/*   Updated: 2022/07/26 21:29:02 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_countwords(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			count++;
			while (*s != c && *s != '\0')
				s++;
		}
	}
	return (count);
}

void	free_all(char **ptr, int k)
{
	while (k != 0)
	{
		free(ptr[k]);
		k--;
	}
	free(ptr);
}

char	**ft_do_tab(char const *s, char c, char **tab, int k)
{
	int	j;
	int	i;

	i = 0;
	while (s[i])
	{	
		if (s[i] == c)
			i++;
		else
		{
			j = 0;
			while ((s[i + j] != c) && (s[i + j] != '\0'))
				j++;
			tab[k] = ft_substr(s, i, j);
			if (!tab[k])
			{
				free_all(tab, k - 1);
				return (0);
			}
			k++;
			i = i + j;
		}	
	}
	tab[k] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	int		k;
	char	**tab;
	int		nombredemots;

	k = 0;
	if (!s)
		return (0);
	nombredemots = ft_countwords(s, c);
	tab = malloc(sizeof(char *) * (nombredemots + 1));
	if (!tab)
		return (0);
	tab = ft_do_tab(s, c, tab, k);
	return (tab);
}
