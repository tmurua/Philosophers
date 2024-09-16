/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:39:32 by tmurua            #+#    #+#             */
/*   Updated: 2024/09/16 19:39:33 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

struct	s_data;

typedef struct s_phil
{
	struct s_data	*dat;
	int				nbr;
	long			t_die;
	int				count_ate;
	pthread_mutex_t	*lt_frk;
	pthread_mutex_t	*rt_frk;
	pthread_mutex_t	m_eating;
	int				f_full;
}					t_phil;

/* f_dth is used as a flag for when a philosopher died and also when all
philosophers have eaten the required times and thereby the dinner finished */
typedef struct s_data
{
	t_phil			*phils;
	int				nbr_phils;
	int				t_dth;
	int				t_eat;
	int				t_slp;
	int				r_eat;
	int				nbr_phils_full;
	int				f_dth;
	pthread_mutex_t	m_dth;
	pthread_t		*tids;
	pthread_mutex_t	*frks;
	long			t_start;
	int				f_print;
	pthread_mutex_t	m_print;
}					t_data;

/*	init.c	*/
int					init_all(t_data *dat, int ac, char **av);
int					init_dat(t_data *dat, int ac, char **av);
int					get_mem(t_data *dat);
void				init_frks(t_data *dat);
void				init_phils(t_data *dat);

/*	utils.c	*/
int					cstm_atoi(char *s);
long				get_msec(void);
void				print_msg(t_phil *phil, char *msg);
int					precise_usleep(long usec);

/*	exit.c	*/
int					error(t_data *dat, char *msg);
void				clean(t_data *dat);

/*	threads.c	*/
int					one_phil(t_data *dat);
void				try_eat(t_phil *phil);
int					is_dead(t_phil *phil);
void				*execute_acts(void *phil_ptr);
int					mlt_phils(t_data *dat);

/*	monitor.c	*/
void				*monitor_dinner(void *dat_ptr);
int					is_late(t_data *dat, int i);
int					is_full(t_data *dat, int i);

/*	acts.c	*/
void				eat(t_phil *phil);
void				take_forks(t_phil *phil);
void				drop_forks(t_phil *phil);
void				nap(t_phil *phil);
void				think(t_phil *phil);
