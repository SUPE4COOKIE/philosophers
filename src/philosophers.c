/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 20:35:37 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/04/19 05:49:12 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void *routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (philo->data->has_started == 0)
		usleep(1000);
	philo->last_meal = get_time_ms();
	if (philo->id % 2 == 0)
		usleep(philo->data->eat_time * 1000);
	if (philo->id % 2 == 0 && philo->id == philo->data->philo_count - 1)
		usleep(philo->data->eat_time * 1000);
	while (philo->data->eat_count == -1 || (int)(philo->meal_count) < philo->data->eat_count)
	{
		if (!philo->alive)
			break ;
		eat(philo);
		if (!philo->alive)
			break ;
		sleep_philo(philo);
		if (!philo->alive)
			break ;
		think(philo);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (parse_args(ac, av, &table) != 0)
		return (1);
	if (init_philos(&table))
		return (1); // free needed
	if (init_mutexes(&table))
		return (1); // free needed
	if (init_threads(&table))
		return (1); // free needed
	return (0);
}
