/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 20:35:37 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/04/08 20:34:40 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void *routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (philo->data->has_started == 0)
		;
	printf("Hello Philosopher %ld\n", philo->id);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (parse_args(ac, av, &table) != 0)
		return (1);
	if (init_philos(&table))
		return (1);
	init_threads(&table);
	return (0);
}
