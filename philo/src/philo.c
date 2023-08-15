/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 08:13:35 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/08/15 16:02:22 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_destroy(pthread_t philo, pthread_mutex_t *mutex_forks)
{
	pthread_join(philo, NULL);
	pthread_mutex_destroy(mutex_forks);
}

int	main(int argc, char *argv[])
{
	static int					i = 0;
	pthread_t					philo[MAX_PHILO];
	pthread_mutex_t				mutex_forks[MAX_PHILO + 1];
	unsigned char				forks[MAX_PHILO + 1];
//	static unsigned char		forks[MAX_PHILO + 1] = {0};
	t_philo						phi_t[MAX_PHILO];

	memset(forks, STATE_IDLE, MAX_PHILO + 1);
	if (check_argv(argc, argv))
	{
		init_mutex(mutex_forks, argv);
		while (++i <= ft_atoi(argv[1]))
		{
			philo_copy(&phi_t[i - 1], argv, forks, mutex_forks);
			philo_copy2(&phi_t[i - 1], argv, argc, i);
			if (i % 2)
				pthread_create(&philo[i - 1], NULL, &philo_odd, &phi_t[i - 1]);
		}
		usleep(STEP);
		while (--i > 0)
			if (i % 2 == 0)
				pthread_create(&philo[i - 1], NULL, &philo_odd, &phi_t[i - 1]);
		while (++i <= ft_atoi(argv[1]))
			join_destroy(philo[i - 1], &mutex_forks[i - 1]);
	}
	return (0);
}
