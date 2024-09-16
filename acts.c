/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:39:13 by tmurua            #+#    #+#             */
/*   Updated: 2024/09/16 19:39:14 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

/* think until 10 ms before death time
if less then 10 ms before death time left then think max 1 ms*/
void	think(t_phil *phil)
{
	print_msg(phil, "is thinking");
	precise_usleep((phil->t_die - get_msec() - 10) * 1000);
}

void	nap(t_phil *phil)
{
	t_data	*dat;

	dat = phil->dat;
	print_msg(phil, "is sleeping");
	precise_usleep(dat->t_slp * 1000);
}

void	drop_forks(t_phil *phil)
{
	pthread_mutex_unlock(phil->rt_frk);
	pthread_mutex_unlock(phil->lt_frk);
}

/* dividing the cases of even and uneven number of philosophers into
different pick up orders mitigates potential deadlocks */
void	take_forks(t_phil *phil)
{
	if (phil->nbr % 2 == 0)
	{
		pthread_mutex_lock(phil->lt_frk);
		print_msg(phil, "has taken a fork");
		pthread_mutex_lock(phil->rt_frk);
		print_msg(phil, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(phil->rt_frk);
		print_msg(phil, "has taken a fork");
		pthread_mutex_lock(phil->lt_frk);
		print_msg(phil, "has taken a fork");
	}
}

void	eat(t_phil *phil)
{
	t_data	*dat;

	dat = phil->dat;
	take_forks(phil);
	pthread_mutex_lock(&(phil->m_eating));
	print_msg(phil, "is eating");
	phil->t_die = get_msec() + dat->t_dth;
	phil->count_ate += 1;
	if (phil->count_ate == dat->r_eat)
	{
		precise_usleep(dat->t_eat * 1000);
		phil->f_full = 1;
		pthread_mutex_unlock(&(phil->m_eating));
		drop_forks(phil);
	}
	else
	{
		pthread_mutex_unlock(&(phil->m_eating));
		precise_usleep(dat->t_eat * 1000);
		drop_forks(phil);
	}
}
