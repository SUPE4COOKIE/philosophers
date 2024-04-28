/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 19:28:01 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/04/28 23:12:49 by mwojtasi         ###   ########.fr       */
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
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_count);
	if (!table->forks)
		return (print_error(ERR_MALLOC));
	while (i < table->philo_count)
	{
		if (pthread_mutex_init(&(table->forks[i]), NULL))
			return (print_error(ERR_MUTEX));
		i++;
	}
	if (pthread_mutex_init(&table->printf, NULL))
		return (print_error(ERR_MUTEX));
	i = 0;
	while (i < table->philo_count)
	{
		table->philosophers[i].meal_count = 0;
		table->philosophers[i].alive = 1;
		i++;
	}
	return (0);
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
			return (print_error(ERR_THREAD));
		i++;
	}
	table->start_time = get_time_ms();
	if (table->start_time == -1)
		return (print_error(ERR_TIME));
	table->has_started = 1;
	ft_sleep(table->die_time); // FIXME: fix ;e ;dr
	while (remaining_alive(table))
	{
		if (death_giver(table))
			break ;
		usleep(100);
	}
	while (i--)
		pthread_join(table->philosophers[i].thread, NULL);
	return (0);
}
