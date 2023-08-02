/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 08:36:41 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/08/02 23:25:47 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_argv(int argc, char *argv[])
{
	if (argc == 5)
	{
		if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[2]) < 1 || ft_atoi(argv[3]) < 1
			|| ft_atoi(argv[4]) < 1)
			return (0);
	}
	else if (argc == 6)
	{
		if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[2]) < 1 || ft_atoi(argv[3]) < 1
			|| ft_atoi(argv[4]) < 1 || ft_atoi(argv[5]) < 1)
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
}

void	philo_copy(t_philo *ptr, char *argv[], char *forks, pthread_mutex_t *mutex_forks)
{
	ptr->id = 0;
	ptr->philo_prop.n_philo = ft_atoi(argv[1]);
	ptr->philo_prop.t_die = ft_atoi(argv[2]);
	ptr->philo_prop.t_eat = ft_atoi(argv[3]);
	ptr->philo_prop.t_sleep = ft_atoi(argv[4]);
	ptr->ptr_mutex_forks = mutex_forks;
	ptr->forks = forks;
}

void	philo_copy2(t_philo *ptr, char *argv[], int argc, int id)
{
	if (argc == 6)
		ptr->philo_prop.n_eat = ft_atoi(argv[5]);
	else
		ptr->philo_prop.n_eat = INT_MAX;
	ptr->id = id;
}

