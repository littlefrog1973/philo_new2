/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 13:13:32 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/08/10 16:09:39 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000L) + (time.tv_usec / 1000L));
}

int	is_die(t_philo *philo)
{
	if (current_time() >= philo->lm_time + (unsigned long) philo->philo_prop.t_die)
		return (1);
	return (0);
}

void	print_log(t_philo *philo, int state)
{
	struct timeval		time;
	unsigned long		millisec;

	gettimeofday(&time, NULL);
	millisec = (time.tv_sec * 1000L) + (time.tv_usec / 1000L) - (unsigned long) philo->s_time;
	if (state == FORK_TAKEN)
	{
		printf("%5lu %3d has taken a fork\n", millisec, philo->id);
	}
	else if (state == STATE_THINKING && philo->state != STATE_THINKING)
	{
		printf("%5lu %3d is thinking\n", millisec, philo->id);
		philo->state = STATE_THINKING;
	}
	else if (state == STATE_EATING)
		printf("%5lu %3d is eating\n", millisec, philo->id);
	else if (state == STATE_SLEEPING)
		printf("%5lu %3d is sleeping\n", millisec, philo->id);
	else if (state == STATE_DEAD)
		printf("%5lu %3d died\n", millisec, philo->id);
}
