/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:36:05 by tmurua            #+#    #+#             */
/*   Updated: 2024/09/16 19:36:52 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

int	main(int ac, char **av)
{
	t_data	*dat;

	dat = 0;
	if (ac == 5 || ac == 6)
	{
		dat = (t_data *)malloc(sizeof(t_data));
		if (init_all(dat, ac, av))
			return (1);
	}
	else
		return (error(dat, "Invalid number of arguments"));
	if (dat->nbr_phils == 1)
		return (one_phil(dat));
	else if (mlt_phils(dat))
		return (1);
	clean(dat);
	return (0);
}
