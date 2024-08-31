/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 02:00:53 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/08/31 14:48:38 by mwojtasi         ###   ########.fr       */
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

void	forks_1st_half(t_fork *forks, int id, int count)
{
	while (forks[id].taken == 1)
		usleep(10);
	pthread_mutex_lock(&(forks[id].fork));
	forks[id].taken = 1;
	while (forks[(id + 1) % count].taken == 1)
		usleep(10);
	pthread_mutex_lock(&(forks[(id + 1) % count].fork));
	forks[(id + 1) % count].taken = 1;
}

void	forks_2nd_half(t_fork *forks, int id, int count)
{
	while (forks[(id + 1) % count].taken == 1)
		usleep(10);
	pthread_mutex_lock(&(forks[(id + 1) % count].fork));
	forks[(id + 1) % count].taken = 1;
	while (forks[id].taken == 1)
		usleep(10);
	pthread_mutex_lock(&(forks[id].fork));
	forks[id].taken = 1;
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
	//forks_1st_half(forks, id, count);
	//if (((id + 1) % count) > id)
	//	forks_1st_half(forks, id, count);
	//else
	//	forks_2nd_half(forks, id, count);
	return (print_forks_taken(philo));
}

int	let_forks(t_philo *philo)
{
	int		id;
	int		count;

	id = philo->id;
	count = philo->data->philo_count;
	if (philo->data->philo_count != 1)
	{
		pthread_mutex_unlock(&(philo->data->forks[(id + 1) % count].fork));
		philo->data->forks[(id + 1) % count].taken = 0;
	}
	pthread_mutex_unlock(&(philo->data->forks[id].fork));
	philo->data->forks[id].taken = 0;
	return (0);
}
