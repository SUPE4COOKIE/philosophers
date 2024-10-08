/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 20:35:37 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/09/03 02:39:19 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include "../includes/actions.h"

void	unsync_threads(t_philo *philo)
{
	if (philo->id % 2 == 0 && philo->data->philo_count != 1)
	{
		ft_sleep(philo->data->eat_time, philo->data);
	}
	if (philo->id % 2 == 0 && philo->id == philo->data->philo_count - 1 \
			&& philo->data->philo_count != 1)
	{
		ft_sleep(philo->data->eat_time, philo->data);
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->data->has_started == 0)
		usleep(10);
	if (philo->data->has_started == 2)
		return (NULL);
	philo->last_meal = get_time_ms();
	unsync_threads(philo);
	while (philo->data->has_started == 1)
	{
		if (!philo->data->has_started)
			break ;
		eat(philo);
		if (philo->data->has_started != 1)
			break ;
		sleep_philo(philo);
		if (philo->data->has_started != 1)
			break ;
		think(philo);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (get_time_ms() == -1)
		return (1);
	if (parse_args(ac, av, &table) != 0)
		return (1);
	if (init_philos(&table))
		return (1);
	if (init_mutexes(&table))
		return (free_table(&table), 1);
	if (init_threads(&table))
		return (free_table(&table), 1);
	free_table(&table);
	return (0);
}
