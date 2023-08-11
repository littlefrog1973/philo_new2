/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 08:13:14 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/08/10 16:31:18 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_time(t_philo *philo)
{
	unsigned long	c_time;

	c_time = current_time();
	philo->s_time = c_time;
	philo->lm_time = c_time;
}

int	taken_fork_odd(t_philo *philo)
{
	int	n_philo;

	n_philo = philo->philo_prop.n_philo;
	if ((philo->forks[philo->id - 1] == 0))
	{
		pthread_mutex_lock(&(philo->ptr_mutex_forks[philo->id - 1]));
		philo->forks[philo->id - 1] = philo->id;
		print_log(philo, FORK_TAKEN);
		if (philo->forks[philo->id % n_philo] == 0)
		{
			pthread_mutex_lock(&(philo->ptr_mutex_forks[philo->id % n_philo]));
			philo->forks[philo->id % n_philo] = philo->id;
			print_log(philo, FORK_TAKEN);
			return (SUCCESS);
		}
/*		else
		{
			philo->forks[philo->id - 1] = 0;
			pthread_mutex_unlock(&(philo->ptr_mutex_forks[philo->id - 1]));
			return (0);
		}
*/
	}
	else if (is_die(philo))
		return (0);
	if ((philo->forks[philo->id - 1] == philo->id) && (philo->forks[philo->id % n_philo] == philo->id))
	{
		return (FORK_TAKEN);
	}
	return (0);
}

int	taken_fork_even(t_philo *philo)
{
	int	n_philo;

	n_philo = philo->philo_prop.n_philo;
	if ((philo->forks[philo->id % n_philo] == 0))
	{
		pthread_mutex_lock(&(philo->ptr_mutex_forks[philo->id % n_philo]));
		philo->forks[philo->id % n_philo] = philo->id;
		print_log(philo, FORK_TAKEN);
		if (philo->forks[philo->id - 1] == 0)
		{
			pthread_mutex_lock(&(philo->ptr_mutex_forks[philo->id - 1]));
			philo->forks[philo->id - 1] = philo->id;
			print_log(philo, FORK_TAKEN);
			return (SUCCESS);
		}
/*		else
		{
			philo->forks[philo->id % n_philo] = 0;
			pthread_mutex_unlock(&(philo->ptr_mutex_forks[philo->id % n_philo]));
			return (0);
		}
*/
	}
	else if (is_die(philo))
		return (0);
	if ((philo->forks[philo->id - 1] == philo->id) && (philo->forks[philo->id % n_philo] == philo->id))
	{
		return (FORK_TAKEN);
	}
	return (0);
}

void release_fork(t_philo *philo, int status)
{
	int	n_philo;

	n_philo = philo->philo_prop.n_philo;
	if (status == STATE_DEAD)
	{
		philo->forks[philo->id - 1] = STATE_DEAD;
		philo->forks[philo->id % n_philo] = 0;
		pthread_mutex_unlock(&(philo->ptr_mutex_forks[philo->id - 1]));
		pthread_mutex_unlock(&(philo->ptr_mutex_forks[philo->id]));
	}
	else
	{
		philo->forks[philo->id - 1] = 0;
		philo->forks[philo->id % n_philo] = 0;
		pthread_mutex_unlock(&(philo->ptr_mutex_forks[philo->id - 1]));
		pthread_mutex_unlock(&(philo->ptr_mutex_forks[philo->id]));
	}
}

void *philo_odd(void *args)
{
	int				n_eat;
	t_philo			*philo;
//	int				pulse;

	philo = (t_philo *) args;
	init_time(philo);
	n_eat = philo->philo_prop.n_eat;
//	pulse = 0;
	while (n_eat)
	{
		if (is_die(philo))
		{
			print_log(philo, STATE_DEAD);
			break;
		}
		print_log(philo, STATE_THINKING);
		while (!taken_fork_odd(philo) && !is_die(philo))
			continue;
		if (is_die(philo))
		{
			print_log(philo, STATE_DEAD);
			break;
		}
//		print_log(philo, FORK_TAKEN);
		philo->lm_time = current_time();
		print_log(philo, STATE_EATING);
		n_eat--;
		usleep(philo->philo_prop.t_eat * 1000);
/*		pulse = 0;
		while (!is_die(philo) && ((pulse * STEP) < (philo->philo_prop.t_eat * 1000)))
		{
			usleep(STEP);
			pulse++;
		}
*/
		if (is_die(philo))
		{
			print_log(philo, STATE_DEAD);
			break;
		}
		release_fork(philo, STATE_SLEEPING);
		print_log(philo, STATE_SLEEPING);
		usleep(philo->philo_prop.t_sleep * 1000);
/*		pulse = 0;
		while (!is_die(philo) && ((pulse * STEP) < (philo->philo_prop.t_sleep * 1000)))
		{
			usleep(STEP);
			pulse++;
		}
*/
		if (is_die(philo))
		{
			print_log(philo, STATE_DEAD);
			break;
		}
	}
	if (taken_fork_odd(philo) == FORK_TAKEN && is_die(philo))
		release_fork(philo, STATE_DEAD);
	return (NULL);
}

void *philo_even(void *args)
{
	int				n_eat;
	t_philo			*philo;
//	int				pulse;

	philo = (t_philo *) args;
	init_time(philo);
	n_eat = philo->philo_prop.n_eat;
//	pulse = 0;
	while (n_eat)
	{
		if (is_die(philo))
		{
			print_log(philo, STATE_DEAD);
			break;
		}
		print_log(philo, STATE_THINKING);
		while (!taken_fork_even(philo) && !is_die(philo))
			continue;
		if (is_die(philo))
		{
			print_log(philo, STATE_DEAD);
			break;
		}
//		print_log(philo, FORK_TAKEN);
		philo->lm_time = current_time();
		print_log(philo, STATE_EATING);
		n_eat--;
		usleep(philo->philo_prop.t_eat * 1000);
/*		pulse = 0;
		while (!is_die(philo) && (pulse * STEP < (philo->philo_prop.t_eat * 1000)))
		{
			usleep(STEP);
			pulse++;
		}
*/
		if (is_die(philo))
		{
			print_log(philo, STATE_DEAD);
			break;
		}
		release_fork(philo, STATE_SLEEPING);
		print_log(philo, STATE_SLEEPING);
		usleep(philo->philo_prop.t_sleep * 1000);
/*		pulse = 0;
		while (!is_die(philo) && (pulse * STEP < (philo->philo_prop.t_sleep * 1000)))
		{
			usleep(STEP);
			pulse++;
		}
*/
		if (is_die(philo))
		{
			print_log(philo, STATE_DEAD);
			break;
		}
	}
	if (taken_fork_even(philo) == FORK_TAKEN && is_die(philo))
		release_fork(philo, STATE_DEAD);
	return (NULL);
}

