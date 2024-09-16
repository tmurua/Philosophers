/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:38:29 by tmurua            #+#    #+#             */
/*   Updated: 2024/09/16 19:38:31 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

/* single philsopher takes the only fork and dies */
int	one_phil(t_data *dat)
{
	dat->t_start = get_msec();
	if (pthread_create(&dat->tids[0], NULL, &execute_acts, &dat->phils[0]))
		return (error(dat, "Unable to create philsopher thread"));
	if (pthread_join(dat->tids[0], NULL))
		return (error(dat, "Unable to join philsopher thread"));
	clean(dat);
	return (0);
}

/* for a single philosopher the left and right fork are the same fork,
trying to lock "both" her forks would result in a deadlock */
void	try_eat(t_phil *phil)
{
	t_data	*dat;

	dat = phil->dat;
	pthread_mutex_lock(phil->lt_frk);
	print_msg(phil, "has taken a fork");
	precise_usleep(dat->t_dth * 1000);
	print_msg(&(dat->phils[0]), "died");
	pthread_mutex_lock(&dat->m_dth);
	dat->f_dth = 1;
	pthread_mutex_unlock(&dat->m_dth);
	pthread_mutex_unlock(phil->lt_frk);
}

int	is_dead(t_phil *phil)
{
	pthread_mutex_lock(&phil->dat->m_dth);
	if (phil->dat->f_dth == 1)
	{
		pthread_mutex_unlock(&phil->dat->m_dth);
		return (1);
	}
	pthread_mutex_unlock(&phil->dat->m_dth);
	return (0);
}

void	*execute_acts(void *phil_ptr)
{
	t_phil	*phil;

	phil = phil_ptr;
	while (!is_dead(phil))
	{
		pthread_mutex_lock(&(phil->m_eating));
		if (phil->f_full)
		{
			pthread_mutex_unlock(&(phil->m_eating));
			break ;
		}
		pthread_mutex_unlock(&(phil->m_eating));
		if (phil->dat->nbr_phils != 1)
		{
			eat(phil);
			nap(phil);
			think(phil);
		}
		else
			try_eat(phil);
	}
	return ((void *)0);
}

int	mlt_phils(t_data *dat)
{
	int			i;
	pthread_t	t_monitor;

	i = 0;
	dat->t_start = get_msec();
	while (i < dat->nbr_phils)
	{
		if (pthread_create(&dat->tids[i], NULL, &execute_acts, &dat->phils[i]))
			return (error(dat, "Unable to create philsopher thread"));
		i++;
	}
	if (pthread_create(&t_monitor, NULL, &monitor_dinner, dat))
		return (error(dat, "Unable to create monitor_dinner thread"));
	i = 0;
	while (i < dat->nbr_phils)
		if (pthread_join(dat->tids[i++], NULL))
			return (error(dat, "Unable to join philsopher threads"));
	if (pthread_join(t_monitor, NULL))
		return (error(dat, "Unable to join monitor_dinner thread"));
	return (0);
}
