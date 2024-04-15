/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 22:29:21 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/04/15 11:04:46 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include "../includes/errors.h"

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (s[count])
		count++;
	return (count);
}

ssize_t	print_error(char *str)
{
	return (write(2, str, ft_strlen(str)));
}

int	init_philos(t_table *table)
{
	int i;

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
	table->forks = malloc(sizeof(t_fork) * table->philo_count);
	if (!table->forks)
		return (print_error(ERR_MALLOC));
	while (i < table->philo_count)
	{
		if (pthread_mutex_init(&(table->forks[i].fork), NULL))
			return (print_error(ERR_MUTEX));
		if (pthread_mutex_init(&(table->forks[i].beeing_checked), NULL))
			return (print_error(ERR_MUTEX));
		i++;
	}
	if (pthread_mutex_init(&table->printf, NULL))
		return (print_error(ERR_MUTEX));
	i = 0;
	while (i < table->philo_count)
	{
		table->forks[i].beeing_used = 0;
		table->philosophers[i].meal_count = 0;
		i++;
	}
	return (0);
}

long long	get_time_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (print_error(ERR_TIME), -1);
	return (long long)((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	init_threads(t_table *table)
{
	int i;

	i = 0;
	table->has_started = 0;
	while (i < table->philo_count)
	{
		if (pthread_create(&table->philosophers[i].thread, NULL, routine, &table->philosophers[i]))
			return (print_error(ERR_THREAD));
		i++;
	}
	table->start_time = get_time_ms();
	if (table->start_time == -1)
		return (print_error(ERR_TIME));
	table->has_started = 1;
	while (i--)
		pthread_join(table->philosophers[i].thread, NULL);
	return (0);
}
