/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 08:13:14 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/08/08 14:40:44 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	prt_state(unsigned long c_time, int id, int *state)
{
	if (*state == STATE_IDLE)
	{
		printf("%lu %d is thinking\n", c_time, id);
		*state = STATE_THINKING;
	}
	else if (*state == STATE_DEAD)
	{
		printf("%lu %d died\n", c_time, id);
	}
}

void *philo_odd(void *args)
{
	int	n_eat;
	int	id;
	t_philo	*ptr_philo;
	int	n_philo;
	int	state;

	state = STATE_IDLE;
	ptr_philo = (t_philo *) args;
	ptr_philo->s_time = ptr_philo->lm_time = current_time();
	id = ptr_philo->id;
	n_eat = ptr_philo->philo_prop.n_eat;
	n_philo = ptr_philo->philo_prop.n_philo;
	while (n_eat)
	{
		if (is_die(ptr_philo))
		{
			state = STATE_DEAD;
			prt_state(current_time(), id, &state);
			break;
		}
		prt_state(current_time(), id, &state);
//		usleep(STEP);
		if (ptr_philo->forks[id - 1] == 0 && !is_die(ptr_philo))
		{
			pthread_mutex_lock(&(ptr_philo->ptr_mutex_forks[id - 1]));
			ptr_philo->forks[id - 1] = id;
			printf("%lu %d has taken a forks\n", current_time(), id);
			if (ptr_philo->forks[id % n_philo] == 0 && !is_die(ptr_philo))
			{
				pthread_mutex_lock(&(ptr_philo->ptr_mutex_forks[id % n_philo]));
				ptr_philo->forks[id % n_philo] = id;
				printf("%lu %d has taken a forks\n", current_time(), id);
				ptr_philo->lm_time = current_time();
				printf("%lu %d is eating\n", current_time(), id);
				usleep(ptr_philo->philo_prop.t_eat * 1000);
				n_eat--;
				ptr_philo->forks[id % n_philo] = 0;
				pthread_mutex_unlock(&(ptr_philo->ptr_mutex_forks[id % n_philo]));
				ptr_philo->forks[id - 1] = 0;
				pthread_mutex_unlock(&(ptr_philo->ptr_mutex_forks[id - 1]));
				printf("%lu %d is sleeping\n", current_time(), id);
				state = STATE_IDLE;
				usleep(ptr_philo->philo_prop.t_sleep * 1000);
			}
			else
				continue;
		}
		else if (ptr_philo->forks[id - 1] == id && !is_die(ptr_philo))
		{
			if (ptr_philo->forks[id % n_philo] == 0 && !is_die(ptr_philo))
			{
				pthread_mutex_lock(&(ptr_philo->ptr_mutex_forks[id % n_philo]));
				ptr_philo->forks[id % n_philo] = id;
				printf("%lu %d has taken a forks\n", current_time(), id);
				ptr_philo->lm_time = current_time();
				printf("%lu %d is eating\n", current_time(), id);
				usleep(ptr_philo->philo_prop.t_eat * 1000);
				n_eat--;
				ptr_philo->forks[id % n_philo] = 0;
				pthread_mutex_unlock(&(ptr_philo->ptr_mutex_forks[id % n_philo]));
				ptr_philo->forks[id - 1] = 0;
				pthread_mutex_unlock(&(ptr_philo->ptr_mutex_forks[id - 1]));
				printf("%lu %d is sleeping\n", current_time(), id);
				state = STATE_IDLE;
				usleep(ptr_philo->philo_prop.t_sleep * 1000);
			}
			else
				continue;
		}
		else if (is_die(ptr_philo))
		{
			if (ptr_philo->forks[id % n_philo] == id)
			{
				ptr_philo->forks[id % n_philo] = 0;
				pthread_mutex_unlock(&(ptr_philo->ptr_mutex_forks[id % n_philo]));
			}
		}
	}
	if (ptr_philo->forks[id - 1] == id && is_die(ptr_philo))
		pthread_mutex_unlock(&(ptr_philo->ptr_mutex_forks[id - 1]));
	else if (ptr_philo->forks[id - 1] != id && ptr_philo->forks[id - 1] > 0)
		{
			while (ptr_philo->forks[id - 1] > 0)
				continue;
			ptr_philo->forks[id - 1] = id;
		}
	return (NULL);
}

void *philo_even(void *args)
{
	int	n_eat;
	int	id;
	t_philo	*ptr_philo;
	int		n_philo;
	int	state;

	state = STATE_IDLE;
	ptr_philo = (t_philo *) args;
	ptr_philo->s_time = ptr_philo->lm_time = current_time();
	id = ptr_philo->id;
	n_eat = ptr_philo->philo_prop.n_eat;
	n_philo = ptr_philo->philo_prop.n_philo;
	while (n_eat)
	{
		if (is_die(ptr_philo))
		{
			state = STATE_DEAD;
			prt_state(current_time(), id, &state);
			break;
		}
		prt_state(current_time(), id, &state);
//		usleep(STEP);
		if (ptr_philo->forks[id % n_philo] == 0 && !is_die(ptr_philo))
		{
			pthread_mutex_lock(&(ptr_philo->ptr_mutex_forks[id % n_philo]));
			ptr_philo->forks[id % n_philo] = id;
			printf("%lu %d has taken a forks\n", current_time(), id);
			if (ptr_philo->forks[id - 1] == 0 && !is_die(ptr_philo))
			{
				pthread_mutex_lock(&(ptr_philo->ptr_mutex_forks[id - 1]));
				ptr_philo->forks[id - 1] = id;
				printf("%lu %d has taken a forks\n", current_time(), id);
				ptr_philo->lm_time = current_time();
				printf("%lu %d is eating\n", current_time(), id);
				usleep(ptr_philo->philo_prop.t_eat * 1000);
				n_eat--;
				ptr_philo->forks[id - 1] = 0;
				pthread_mutex_unlock(&(ptr_philo->ptr_mutex_forks[id - 1]));
				ptr_philo->forks[id % n_philo] = 0;
				pthread_mutex_unlock(&(ptr_philo->ptr_mutex_forks[id % n_philo]));
				printf("%lu %d is sleeping\n", current_time(), id);
				state = STATE_IDLE;
				usleep(ptr_philo->philo_prop.t_sleep * 1000);
			}
			else
				continue;
		}
		else if(ptr_philo->forks[id % n_philo] == id && !is_die(ptr_philo))
		{
			if (ptr_philo->forks[id - 1] == 0 && !is_die(ptr_philo))
			{
				pthread_mutex_lock(&(ptr_philo->ptr_mutex_forks[id - 1]));
				ptr_philo->forks[id - 1] = id;
				printf("%lu %d has taken a forks\n", current_time(), id);
				ptr_philo->lm_time = current_time();
				printf("%lu %d is eating\n", current_time(), id);
//				state = STATE_IDLE;
				usleep(ptr_philo->philo_prop.t_eat * 1000);
				n_eat--;
				ptr_philo->forks[id - 1] = 0;
				pthread_mutex_unlock(&(ptr_philo->ptr_mutex_forks[id - 1]));
				ptr_philo->forks[id % n_philo] = 0;
				pthread_mutex_unlock(&(ptr_philo->ptr_mutex_forks[id % n_philo]));
				printf("%lu %d is sleeping\n", current_time(), id);
				state = STATE_IDLE;
				usleep(ptr_philo->philo_prop.t_sleep * 1000);
			}
			else
				continue;
		}
		else if (is_die(ptr_philo))
		{
			if (ptr_philo->forks[id % n_philo] == id)
			{
				ptr_philo->forks[id % n_philo] = 0;
				pthread_mutex_unlock(&(ptr_philo->ptr_mutex_forks[id % n_philo]));
			}
		}
	}
	if (ptr_philo->forks[id - 1] == id && is_die(ptr_philo))
		pthread_mutex_unlock(&(ptr_philo->ptr_mutex_forks[id - 1]));
	else if (ptr_philo->forks[id - 1] != id && ptr_philo->forks[id - 1] > 0)
		{
			while (ptr_philo->forks[id - 1] > 0)
				continue;
			ptr_philo->forks[id - 1] = id;
		}
	return (NULL);
}
