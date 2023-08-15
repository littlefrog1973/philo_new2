/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 08:13:14 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/08/15 16:52:30 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eat_sleep(t_philo *philo, int *n_eat)
{
	pthread_mutex_lock(&(philo->mtx_forks[philo->id % philo->prop.n_phi]));
	philo->forks[philo->id % philo->prop.n_phi] = philo->id;
	print_log(philo, FORK_TAKEN);
	philo->lm_time = current_time();
	print_log(philo, STATE_EATING);
	while (current_time() < (philo->lm_time + philo->prop.t_eat))
	{
		usleep(STEP);
		if (is_die(philo))
			return (1);
	}
	*n_eat = *n_eat - 1;
	philo->forks[philo->id % philo->prop.n_phi] = 0;
	pthread_mutex_unlock(&(philo->mtx_forks[philo->id % philo->prop.n_phi]));
	philo->forks[philo->id - 1] = 0;
	pthread_mutex_unlock(&(philo->mtx_forks[philo->id - 1]));
	print_log(philo, STATE_SLEEPING);
	while (current_time() < (philo->lm_time + philo->prop.t_eat
			+ philo->prop.t_sleep))
	{
		usleep(STEP);
		if (is_die(philo))
			return (1);
	}
	return (0);
}

void	do_after_dead(t_philo *philo)
{
			if (philo->forks[philo->id - 1] == philo->id)
			{
				philo->forks[philo->id - 1] = STATE_DEAD;
				pthread_mutex_unlock(&(philo->mtx_forks[philo->id - 1]));
			}
			if (philo->forks[philo->id % philo->prop.n_phi] == philo->id)
			{
				philo->forks[philo->id % philo->prop.n_phi] = 0;
				pthread_mutex_unlock(&(philo->mtx_forks[philo->id
						% philo->prop.n_phi]));
			}
			philo->forks[MAX_PHILO] = STATE_DEAD;
}

void	*philo_odd(void *args)
{
	int		n_eat;
	t_philo	*philo;

	philo = (t_philo *) args;
	init_time(philo);
	n_eat = philo->prop.n_eat;
	while (n_eat)
	{
		print_log(philo, STATE_THINKING);
		if ((philo->forks[philo->id - 1] == STATE_IDLE ||
			philo->forks[philo->id - 1] == philo->id) && !is_die(philo))
		{
			if (philo->forks[philo->id - 1] == STATE_IDLE)
			{
				pthread_mutex_lock(&(philo->mtx_forks[philo->id - 1]));
				philo->forks[philo->id - 1] = philo->id;
				print_log(philo, FORK_TAKEN);
			}
			if (!philo->forks[philo->id % philo->prop.n_phi] && !is_die(philo))
			{
				if (eat_sleep(philo, &n_eat))
					break ;
			}
			else
				continue ;
		}
		else if (is_die(philo))
		{
			print_log(philo, STATE_DEAD);
			do_after_dead(philo);
			break ;
		}
	}
	return (NULL);
}
