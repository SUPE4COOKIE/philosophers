/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 22:29:21 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/04/27 19:49:01 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include "../includes/errors.h"
#include "../includes/actions.h"

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

void	free_table(t_table *table)
{
	int	i;

	i = 0;
	if (table->philosophers)
		free(table->philosophers);
	if (table->forks)
	{
		while (i < table->philo_count)
		{
			pthread_mutex_destroy(&table->forks[i]);
			i++;
		}
		free(table->forks);
	}
}

int	all_have_eaten(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_count)
	{
		if ((int)(table->philosophers[i].meal_count) < table->eat_count)
			return (0);
		i++;
	}
	return (1);
}

int	print_status(t_philo *philo, char *status)
{
	if (philo->data->has_started == 0)
		return (0);
	if (pthread_mutex_lock(&philo->data->printf) != 0)
		return (print_error(ERR_MUTEX_LOCK));
	if (printf("%lld %d %s\n",
			get_time_ms() - philo->data->start_time,
			philo->id + 1,
			status) < 0)
		return (print_error(ERR_PRINTF));
	pthread_mutex_unlock(&philo->data->printf);
	return (0);
}
