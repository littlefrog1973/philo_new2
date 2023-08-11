/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 08:13:35 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/08/10 16:59:36 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	static int		i = 0;
	pthread_t		philo[MAX_PHILO];
	pthread_mutex_t	mutex_forks[MAX_PHILO];
	volatile int	forks[MAX_PHILO] = {0};
//	static int		forks[MAX_PHILO] = {0};
	t_philo			phi_t[MAX_PHILO];

	if (check_argv(argc, argv))
	{
		init_mutex(mutex_forks, argv);
/*		while (i <= ft_atoi(argv[1]))
		{
			philo_copy(&phi_t[i - 1], argv, forks, mutex_forks);
			philo_copy2(&phi_t[i - 1], argv, argc, i);
			pthread_create(&philo[i - 1], NULL, &philo_odd, &phi_t[i - 1]);
			i+=2;
		}
		i = 2;
		usleep(STEP);
		while (i <= ft_atoi(argv[1]))
		{
			philo_copy(&phi_t[i - 1], argv, forks, mutex_forks);
			philo_copy2(&phi_t[i - 1], argv, argc, i);
			pthread_create(&philo[i - 1], NULL, &philo_even, &phi_t[i - 1]);
			i+=2;
		}
*/
		while (++i <= ft_atoi(argv[1]))
		{
			philo_copy(&phi_t[i - 1], argv, forks, mutex_forks);
			philo_copy2(&phi_t[i - 1], argv, argc, i);
			if ((i % 2))
				pthread_create(&philo[i - 1], NULL, &philo_odd, &phi_t[i - 1]);
			else
				pthread_create(&philo[i - 1], NULL, &philo_even, &phi_t[i - 1]);
		}
//		i = ft_atoi(argv[1]);
		while (--i > 0)
		{
			pthread_join(philo[i - 1], NULL);
			pthread_mutex_destroy(&mutex_forks[i - 1]);
		}
	}
	return (0);
}
