/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:38:02 by tmurua            #+#    #+#             */
/*   Updated: 2024/09/16 19:38:05 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

/* set phils[i].f_full = -2 after counting the respective philosopher
to not count her multiple times into nbr_phils_full.
message = NULL to print that every philospher has eaten the required times */
int	is_full(t_data *dat, int i)
{
	if (dat->phils[i].f_full == 1)
	{
		dat->nbr_phils_full += 1;
		dat->phils[i].f_full = -2;
	}
	if (dat->nbr_phils_full >= dat->nbr_phils)
	{
		print_msg(&(dat->phils[i]), NULL);
		pthread_mutex_lock(&(dat->m_dth));
		dat->f_dth = 1;
		pthread_mutex_unlock(&(dat->m_dth));
		return (1);
	}
	return (0);
}

int	is_late(t_data *dat, int i)
{
	if (!dat->phils[i].f_full && dat->phils[i].t_die <= get_msec())
	{
		print_msg(&(dat->phils[i]), "died");
		pthread_mutex_lock(&(dat->m_dth));
		dat->f_dth = 1;
		pthread_mutex_unlock(&(dat->m_dth));
		return (1);
	}
	return (0);
}

/* while a philosopher is eating he can not die */
void	*monitor_dinner(void *dat_ptr)
{
	t_data	*dat;
	int		i;

	dat = dat_ptr;
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&(dat->phils[i].m_eating));
		if (is_late(dat, i) || is_full(dat, i))
		{
			pthread_mutex_unlock(&(dat->phils[i].m_eating));
			return ((void *)0);
		}
		pthread_mutex_unlock(&(dat->phils[i].m_eating));
		i++;
		if (i >= dat->nbr_phils)
			i = 0;
	}
	return ((void *)0);
}
