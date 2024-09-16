/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:37:36 by tmurua            #+#    #+#             */
/*   Updated: 2024/09/16 19:37:40 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

int	init_all(t_data *dat, int ac, char **av)
{
	if (init_dat(dat, ac, av))
		return (1);
	if (get_mem(dat))
		return (1);
	init_frks(dat);
	init_phils(dat);
	return (0);
}

/* req_eat set to -2 if no number_of_times_each_philsopher_must_eat
is specified;
cstm_atoi() returns -1 in case of invalid arguments */
int	init_dat(t_data *dat, int ac, char **av)
{
	dat->nbr_phils = cstm_atoi(av[1]);
	dat->t_dth = cstm_atoi(av[2]);
	dat->t_eat = cstm_atoi(av[3]);
	dat->t_slp = cstm_atoi(av[4]);
	if (ac == 6)
		dat->r_eat = cstm_atoi(av[5]);
	else if (ac == 5)
		dat->r_eat = -2;
	dat->f_dth = 0;
	dat->nbr_phils_full = 0;
	dat->tids = 0;
	dat->frks = 0;
	dat->phils = 0;
	dat->t_start = 0;
	dat->f_print = 1;
	if (dat->nbr_phils < 1 || dat->t_dth == -1 || dat->t_eat == -1
		|| dat->t_slp == -1 || dat->r_eat == -1 || dat->r_eat == 0)
		return (error(dat, "Invalid arguments"));
	pthread_mutex_init(&dat->m_dth, NULL);
	pthread_mutex_init(&dat->m_print, NULL);
	return (0);
}

int	get_mem(t_data *dat)
{
	dat->tids = malloc(sizeof(pthread_t) * dat->nbr_phils);
	if (!dat->tids)
		return (error(dat, "Unable to allocate thread IDs"));
	dat->frks = malloc(sizeof(pthread_mutex_t) * dat->nbr_phils);
	if (!dat->frks)
		return (error(dat, "Unable to allocate forks"));
	dat->phils = malloc(sizeof(t_phil) * dat->nbr_phils);
	if (!dat->phils)
		return (error(dat, "Unable to allocate philsophers"));
	return (0);
}

void	init_frks(t_data *dat)
{
	int	i;

	i = 0;
	while (i < dat->nbr_phils)
		pthread_mutex_init(&dat->frks[i++], NULL);
	i = 0;
	while (i < dat->nbr_phils)
	{
		dat->phils[i].lt_frk = &dat->frks[i];
		dat->phils[i].rt_frk = &dat->frks[(i + 1) % dat->nbr_phils];
		i++;
	}
}

void	init_phils(t_data *dat)
{
	int	i;

	i = 0;
	while (i < dat->nbr_phils)
	{
		dat->phils[i].nbr = i + 1;
		dat->phils[i].t_die = get_msec() + dat->t_dth;
		dat->phils[i].count_ate = 0;
		dat->phils[i].dat = dat;
		pthread_mutex_init(&dat->phils[i].m_eating, NULL);
		dat->phils[i].f_full = 0;
		i++;
	}
}
