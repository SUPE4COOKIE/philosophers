/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 19:28:01 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/09/03 02:49:07 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include "../includes/errors.h"
#include "../includes/actions.h"

int	init_philos(t_table *table)
{
	int	i;

	i = 0;
	table->philosophers = malloc(sizeof(t_philo) * table->philo_count);
	if (!table->philosophers)
		return (print_error(ERR_MALLOC));
	while (i < table->philo_count)
	{
		table->philosophers[i].id = i;
		table->philosophers[i].last_meal = 0;
		table->philosophers[i].meal_count = 0;
		table->philosophers[i].data = table;
		i++;
	}
	return (0);
}

int	init_mutexes(t_table *table)
{
	int	i;

	i = 0;
	table->forks = (t_fork *)malloc(sizeof(t_fork) * table->philo_count);
	if (!table->forks)
		return (print_error(ERR_MALLOC));
	while (i < table->philo_count)
	{
		table->forks[i].taken = 0;
		if (pthread_mutex_init(&(table->forks[i].fork), NULL))
			return (free_forks_until_n(table, i), print_error(ERR_MUTEX));
		i++;
	}
	if (pthread_mutex_init(&table->printf, NULL))
		return (free_no_printf(table), print_error(ERR_MUTEX));
	return (0);
}

void	free_threads_until_n(t_table *table, int n)
{
	table->has_started = 2;
	while (n--)
		pthread_join(table->philosophers[n].thread, NULL);
}

int	init_threads(t_table *table)
{
	int	i;

	i = 0;
	table->has_started = 0;
	while (i < table->philo_count)
	{
		if (pthread_create(&table->philosophers[i].thread, NULL,
				routine, &table->philosophers[i]))
			return (free_threads_until_n(table, i), print_error(ERR_THREAD));
		i++;
	}
	table->start_time = get_time_ms();
	table->has_started = 1;
	while (1)
	{
		if (death_giver(table))
			break ;
		if (meal_ender(table))
			break ;
		usleep(100);
	}
	while (i--)
		pthread_join(table->philosophers[i].thread, NULL);
	return (0);
}
