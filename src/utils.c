/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 22:29:21 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/04/30 16:11:45 by mwojtasi         ###   ########.fr       */
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

int	print_status(t_philo *philo, char *status)
{
	if (pthread_mutex_lock(&philo->data->printf) != 0)
		return (print_error(ERR_MUTEX_LOCK));
	if (philo->data->has_started == 0)
		return (pthread_mutex_unlock(&philo->data->printf), 0);
	if (printf("%lld %d %s\n",
			get_time_ms() - philo->data->start_time,
			philo->id + 1,
			status) < 0)
		return (print_error(ERR_PRINTF));
	pthread_mutex_unlock(&philo->data->printf);
	return (0);
}

int	print_forks_taken(t_philo *philo)
{
	if (print_status(philo, FORK_TAKEN))
		return (1);
	if (print_status(philo, FORK_TAKEN))
		return (1);
	return (0);
}
