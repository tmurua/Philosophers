/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:37:15 by tmurua            #+#    #+#             */
/*   Updated: 2024/09/16 19:37:18 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

int	error(t_data *dat, char *msg)
{
	if (dat)
	{
		if (dat->tids)
			free(dat->tids);
		if (dat->frks)
			free(dat->frks);
		if (dat->phils)
			free(dat->phils);
		free(dat);
	}
	printf("Error: %s\n", msg);
	return (1);
}

void	clean(t_data *dat)
{
	int	i;

	pthread_mutex_destroy(&dat->m_dth);
	pthread_mutex_destroy(&dat->m_print);
	i = 0;
	while (i < dat->nbr_phils)
	{
		pthread_mutex_destroy(&dat->frks[i]);
		pthread_mutex_destroy(&dat->phils[i].m_eating);
		i++;
	}
	if (dat->tids)
		free(dat->tids);
	if (dat->frks)
		free(dat->frks);
	if (dat->phils)
		free(dat->phils);
	if (dat)
		free(dat);
}
