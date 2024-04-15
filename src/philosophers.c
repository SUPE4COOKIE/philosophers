/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 20:35:37 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/04/15 12:02:10 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void *routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (philo->data->has_started == 0)
		;
	philo->last_meal = get_time_ms();
	while (1)
	{
		eat(philo);
		sleep_philo(philo);
		think(philo);
	}
	while (philo->data->philo_count != philo->id)
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
