/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:03:17 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/04/24 16:24:40 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include "../includes/errors.h"
#include "../includes/actions.h"

int	print_status(t_philo *philo, char *status)
{
	if (philo->data->has_started == 0)
		return (0);
	if (pthread_mutex_lock(&philo->data->printf) != 0)
		return (print_error(ERR_MUTEX_LOCK));
	if (printf("%lld %d %s\n", get_time_ms() - philo->data->start_time, philo->id + 1, status) < 0)
		return (print_error(ERR_PRINTF));
	pthread_mutex_unlock(&philo->data->printf);
	return (0);
}

int	take_forks(t_philo *philo)
{
	pthread_mutex_t	*forks;
	int				id;
	int				count;

	forks = philo->data->forks;
	id = philo->id;
	count = philo->data->philo_count;
	if (((id + 1) % count) < id)
	{
		if (pthread_mutex_lock(&(forks[(id + 1) % count])) != 0)
			return (print_error(ERR_MUTEX));
		if (pthread_mutex_lock(&(forks[id])) != 0)
			return (print_error(ERR_MUTEX_LOCK));
	}
	else
	{
		if (pthread_mutex_lock(&(forks[id])) != 0)
			return (print_error(ERR_MUTEX_LOCK));
		if (pthread_mutex_lock(&(forks[(id + 1) % count])) != 0)
			return (print_error(ERR_MUTEX));
	}
	print_status(philo, FORK_TAKEN);
	print_status(philo, FORK_TAKEN);
	return (0);
}

int	let_forks(t_philo *philo)
{
	int		id;
	int		count;

	id = philo->id;
	count = philo->data->philo_count;
	if (pthread_mutex_unlock(&(philo->data->forks[(id + 1) % count])) != 0)
		return (print_error(ERR_MUTEX_UNLOCK));
	if (pthread_mutex_unlock(&(philo->data->forks[id])) != 0)
		return (print_error(ERR_MUTEX_UNLOCK));
	return (0);
}

int	eat(t_philo *philo)
{
	if (take_forks(philo))
		return (1);
	if (print_status(philo, EATING))
		return (1);
	philo->last_meal = get_time_ms();
	philo->meal_count++;
	usleep(philo->data->eat_time * 1000);
	if (let_forks(philo))
		return (1);
	return (0);
}

int	sleep_philo(t_philo *philo)
{
	if (print_status(philo, SLEEPING))
		return (1);
	if (usleep(philo->data->sleep_time * 1000) < 0)
		return (print_error(ERR_USLEEP));
	return (0);
}

int	think(t_philo *philo)
{
	if (print_status(philo, THINKING))
		return (1);
	return (0);
}

