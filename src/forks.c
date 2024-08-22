/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 02:00:53 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/08/22 02:44:54 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include "../includes/errors.h"
#include "../includes/actions.h"

int	single_fork(t_philo *philo)
{
	t_fork	*forks;
	int		id;

	forks = philo->data->forks;
	id = philo->id;
	if (pthread_mutex_lock(&(forks[id].fork)) != 0)
		return (print_error(ERR_MUTEX_LOCK));
	print_status(philo, FORK_TAKEN);
	while (philo->data->has_started == 1)
		usleep(100);
	return (0);
}

int	take_forks(t_philo *philo)
{
	t_fork	*forks;
	int		id;
	int		count;

	forks = philo->data->forks;
	id = philo->id;
	count = philo->data->philo_count;
	if (philo->data->philo_count == 1)
		return (single_fork(philo));
	if (((id + 1) % count) > id)
	{
		pthread_mutex_lock(&(forks[id].fork));
		forks[id].taken = 1;
		pthread_mutex_lock(&(forks[(id + 1) % count].fork));
		forks[(id + 1) % count].taken = 1;
	}
	else
	{
		pthread_mutex_lock(&(forks[(id + 1) % count].fork));
		forks[(id + 1) % count].taken = 1;
		pthread_mutex_lock(&(forks[id].fork));
		forks[id].taken = 1;
	}
	return (print_forks_taken(philo));
}

int	let_forks(t_philo *philo)
{
	int		id;
	int		count;

	id = philo->id;
	count = philo->data->philo_count;
	if (philo->data->philo_count != 1)
		if (pthread_mutex_unlock(&(philo->data->forks[(id + 1) % count].fork)) != 0)
			return (print_error(ERR_MUTEX_UNLOCK));
	if (pthread_mutex_unlock(&(philo->data->forks[id].fork)) != 0)
		return (print_error(ERR_MUTEX_UNLOCK));
	return (0);
}