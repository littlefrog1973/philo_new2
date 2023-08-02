/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:57:11 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/06/09 23:29:03 by sdeeyien         ###   ########.fr       */
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

typedef struct s_philo_prop
{
	int	n_philo;
	int	t_die;
	int	t_eat;
	int t_sleep;
	int n_eat;
}	t_philo_prop;

typedef struct  s_philo
{
	int				id;
	t_philo_prop	philo_prop;
	pthread_mutex_t	*ptr_mutex_forks;
	char			*forks;
	unsigned long	s_time;
	unsigned long	lm_time;
}	t_philo;

#define	MAX_PHILO		200
#define STATE_IDLE		0
#define	STATE_THINKING	1
#define	STATE_EATING	2
#define	STATE_SLEEPING	4
#define	STATE_DEAD		8
#define	FORK_TAKEN		4
#define	STEP			200

/* init.c*/
int	check_argv(int argc, char *argv[]);
void	init_mutex(pthread_mutex_t *forks, char **argv);
void	philo_copy(t_philo *ptr, char *argv[], pthread_mutex_t *mutex_forks,
	char *forks);
void	philo_copy2(t_philo *ptr, char *argv[], int argc, int id);
/* ft_atoi.c */
int	ft_atoi(const char *str);

/* pthread.c*/
void *philo_odd(void *args);
void *philo_even(void *args);

/* utils.c*/
unsigned long	current_time(void);
int	is_die(t_philo *philo);

#endif