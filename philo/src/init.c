/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 08:36:41 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/08/15 15:56:08 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_argv(int argc, char *argv[])
{
	if (argc == 5)
	{
		if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[2]) < 1 || ft_atoi(argv[3]) < 1
			|| ft_atoi(argv[4]) < 1 || ft_atoi(argv[1]) > MAX_PHILO)
			return (0);
	}
	else if (argc == 6)
	{
		if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[2]) < 1 || ft_atoi(argv[3]) < 1
			|| ft_atoi(argv[4]) < 1 || ft_atoi(argv[5]) < 1
			|| ft_atoi(argv[1]) > MAX_PHILO)
			return (0);
	}
	else if ((argc < 5) || (argc > 6))
		return (0);
	return (1);
}

void	init_mutex(pthread_mutex_t *mutex_forks, char **argv)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		pthread_mutex_init(&mutex_forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&mutex_forks[MAX_PHILO], NULL);
}

void	philo_copy(t_philo *ptr, char *argv[], unsigned char *forks,
			pthread_mutex_t *mutex_forks)
{
	ptr->id = 0;
	ptr->prop.n_phi = ft_atoi(argv[1]);
	ptr->prop.t_die = ft_atoi(argv[2]);
	ptr->prop.t_eat = ft_atoi(argv[3]);
	ptr->prop.t_sleep = ft_atoi(argv[4]);
	ptr->mtx_forks = mutex_forks;
	ptr->forks = forks;
}

void	philo_copy2(t_philo *ptr, char *argv[], int argc, int id)
{
	if (argc == 6)
		ptr->prop.n_eat = ft_atoi(argv[5]);
	else
		ptr->prop.n_eat = INT_MAX;
	ptr->id = id;
}
