/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:57:11 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/08/16 00:10:06 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_prop
{
	int	n_phi;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	n_eat;
}	t_prop;

typedef struct s_philo
{
	int				id;
	t_prop			prop;
	pthread_mutex_t	*mtx_forks;
	unsigned char	*forks;
	unsigned long	s_time;
	unsigned long	lm_time;
	char			state;
}	t_philo;

# define MAX_PHILO		200
# define IDLE			0
# define STATE_THINKING	1
# define STATE_EATING	2
# define STATE_SLEEPING	4
# define STATE_DEAD		255
# define FORK_TAKEN		3
# define STEP			50

/* init.c*/
int				check_argv(int argc, char *argv[]);
void			init_mutex(pthread_mutex_t *forks, char **argv);
void			philo_copy(t_philo *ptr, char *argv[], unsigned char *forks,
					pthread_mutex_t *mutex_forks);
void			philo_copy2(t_philo *ptr, char *argv[], int argc, int id);

/* ft_atoi.c */
int				ft_atoi(const char *str);

/* pthread.c*/
void			*philo_odd(void *args);

/* utils.c*/
unsigned long	current_time(void);
int				is_die(t_philo *philo);
void			init_time(t_philo *philo);
void			print_log(t_philo *philo, int state);

#endif
