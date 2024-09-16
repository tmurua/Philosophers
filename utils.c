/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:35:50 by tmurua            #+#    #+#             */
/*   Updated: 2024/09/16 19:35:54 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

int	cstm_atoi(char *s)
{
	int					i;
	unsigned long long	v;

	i = 0;
	while (s[i] == 32 || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (!s[i] || s[i] == '-' || ((s[i] == '+')
			&& !(s[i + 1] >= '0' && s[i + 1] <= '9')))
		return (-1);
	if (s[i] == '+')
		i++;
	v = 0;
	while (s[i])
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (-1);
		else
			v = v * 10 + (s[i] - '0');
		i++;
	}
	if (v > INT_MAX)
		return (-1);
	return ((int)v);
}

/* tv_sec contains the number of seconds since some epoch (like the UNIX epoch),
and tv_usec contains the number of microseconds within that second */
long	get_msec(void)
{
	long			msec;
	struct timeval	time;

	if (!gettimeofday(&time, NULL))
	{
		msec = (time.tv_sec * 1000) + (time.tv_usec / 1000);
		return (msec);
	}
	return (1);
}

/* after all philosophers have eaten the required times no more
messages are printed */
void	print_msg(t_phil *phil, char *msg)
{
	long	t;
	t_data	*dat;

	t = 0;
	dat = phil->dat;
	if (msg == NULL)
	{
		pthread_mutex_lock(&dat->m_print);
		t = get_msec() - dat->t_start;
		if (dat->r_eat == 1)
			printf("%ld all philosophers have eaten %d time\n", t, dat->r_eat);
		if (dat->r_eat > 1)
			printf("%ld all philosophers have eaten %d times\n", t, dat->r_eat);
		dat->f_print = 0;
		pthread_mutex_unlock(&dat->m_print);
	}
	else if (!is_dead(phil))
	{
		pthread_mutex_lock(&dat->m_print);
		t = get_msec() - dat->t_start;
		if (dat->f_print)
			printf("%ld %d %s\n", t, phil->nbr, msg);
		pthread_mutex_unlock(&dat->m_print);
	}
}

/* loop until we reach usec and check every 1/1000 usec whether we
reached usec to be three orders of magnitude more precise */
int	precise_usleep(long usec)
{
	long	start;

	start = get_msec();
	while ((get_msec() - start) * 1000 < usec)
	{
		if (usleep(usec / 1000) == -1)
			return (-1);
	}
	return (0);
}
