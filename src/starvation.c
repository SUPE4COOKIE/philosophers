/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starvation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 19:29:46 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/08/31 20:44:41 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include "../includes/actions.h"

__attribute__((hot)) int	death_giver(t_table *table)
{
	int	i;

	i = 0;
	if (get_time_ms() - table->start_time < table->die_time)
		return (0);
	while (i < table->philo_count)
	{
		if (get_time_ms()
			- table->philosophers[i].last_meal > table->die_time)
		{
			table->has_started = 0;
			pthread_mutex_lock(&table->philosophers[i].data->printf);
			printf("%lld %d %s\n",
				get_time_ms() - table->start_time,
				table->philosophers[i].id + 1, DEAD);
			usleep(1000);
			pthread_mutex_unlock(&table->philosophers[i].data->printf);
			return (1);
		}
		i++;
	}
	return (0);
}

__attribute__((hot)) int	meal_ender(t_table *table)
{
	int	i;

	i = 0;
	if (table->eat_count == -1)
		return (0);
	while (i < table->philo_count)
	{
		if ((int)(table->philosophers[i].meal_count) < table->eat_count)
			return (0);
		i++;
	}
	table->has_started = 2;
	return (1);
}
