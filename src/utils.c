/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 22:29:21 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/04/08 20:35:14 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

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
		return (1);
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

void	init_threads(t_table *table)
{
	int i;

	i = 0;
	while (i < table->philo_count)
	{
		pthread_create(&table->philosophers[i].thread, NULL, routine, &table->philosophers[i]);
		i++;
	}
	table->has_started = 1;
	while (i--)
		pthread_join(table->philosophers[i].thread, NULL);
}
