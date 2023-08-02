/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 08:13:35 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/06/06 17:15:28 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char *argv[])
{
	int				i;
	pthread_t		philo[MAX_PHILO];
	pthread_mutex_t	mutex_forks[MAX_PHILO];
	char			forks[MAX_PHILO];
	t_philo			*ptr[MAX_PHILO];

	if(check_argv(argc, argv))
	{
		i = 0;
		while (++i <= ft_atoi(argv[1]))
		{
			ptr[i - 1] = malloc(sizeof(t_philo));
			philo_copy(ptr[i - 1], argv, mutex_forks, forks);
			philo_copy2(ptr[i - 1], argv, argc, i);
			ptr[i - 1]->id = i;
			if ((i % 2))
				pthread_create(&philo[i - 1], NULL, &philo_odd, ptr[i - 1]);
			else
				pthread_create(&philo[i - 1], NULL, &philo_even, ptr[i - 1]);
		}
		while (--i > 0)
		{
			pthread_join(philo[i - 1], NULL);
			free(ptr[i - 1]);
			pthread_mutex_destroy(&mutex_forks[i - 1]);
		}
	}
	return (0);
}
