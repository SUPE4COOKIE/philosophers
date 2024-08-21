/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:53:16 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/04/30 18:32:42 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	free_table(t_table *table)
{
	if (table->philosophers)
		free(table->philosophers);
	if (table->forks)
	{
		free_forks_until_n(table, table->philo_count);
		pthread_mutex_destroy(&table->printf);
	}
}

void	free_no_printf(t_table *table)
{
	if (table->philosophers)
	{
		free(table->philosophers);
		table->philosophers = NULL;
	}
	if (table->forks)
		free_forks_until_n(table, table->philo_count);
}

void	free_forks_until_n(t_table *table, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&table->forks[i].fork);
		i++;
	}
	free(table->forks);
	table->forks = NULL;
}
