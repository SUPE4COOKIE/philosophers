/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:03:17 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/04/27 21:03:20 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include "../includes/errors.h"
#include "../includes/actions.h"

int	single_fork(t_philo *philo)
{
	pthread_mutex_t	*forks;
	int				id;

	forks = philo->data->forks;
	id = philo->id;
	if (pthread_mutex_lock(&(forks[id])) != 0)
		return (print_error(ERR_MUTEX_LOCK));
	print_status(philo, FORK_TAKEN);
	while (philo->data->has_started == 1)
		ft_sleep(1);
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
	if (philo->data->philo_count == 1)
		return (single_fork(philo));
	if (((id + 1) % count) > id)
	{
		if (pthread_mutex_lock(&(forks[id])) != 0)
			return (print_error(ERR_MUTEX_LOCK));
		if (pthread_mutex_lock(&(forks[(id + 1) % count])) != 0)
			return (print_error(ERR_MUTEX));
	}
	else
	{
		if (pthread_mutex_lock(&(forks[(id + 1) % count])) != 0)
			return (print_error(ERR_MUTEX));
		if (pthread_mutex_lock(&(forks[id])) != 0)
			return (print_error(ERR_MUTEX_LOCK));
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
	if (philo->data->philo_count != 1)
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
	if (philo->data->has_started == 0)
		return (let_forks(philo));
	if (print_status(philo, EATING))
		return (1);
	philo->meal_count++;
	ft_sleep(philo->data->eat_time);
	philo->last_meal = get_time_ms();
	if (let_forks(philo))
		return (1);
	return (0);
}

int	sleep_philo(t_philo *philo)
{
	if (print_status(philo, SLEEPING))
		return (1);
	ft_sleep(philo->data->sleep_time);
	return (0);
}

int	think(t_philo *philo)
{
	if (print_status(philo, THINKING))
		return (1);
	ft_sleep(1);
	return (0);
}
