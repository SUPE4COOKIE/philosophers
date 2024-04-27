/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starvation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 19:29:46 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/04/27 19:53:29 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include "../includes/actions.h"

int	death_giver(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_count)
	{
		if (table->philosophers[i].alive == 1)
		{
			if (get_time_ms()
				- table->philosophers[i].last_meal > table->die_time)
			{
				print_status(&table->philosophers[i], DEAD);
				table->has_started = 0;
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	remaining_alive(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_count)
	{
		if (table->philosophers[i].alive == 1)
			return (1);
		i++;
	}
	return (0);
}
