/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:03:17 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/04/14 09:44:43 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include "../includes/errors.h"
#include "../includes/actions.h"

int	print_status(t_philo *philo, char *status)
{
	if (pthread_mutex_lock(&philo->data->printf) != 0)
		return (print_error(ERR_MUTEX_LOCK));
	if (printf("%lld %d %s\n", get_time_ms() - philo->data->start_time, philo->id, status) < 0)
		return (print_error(ERR_PRINTF));
	pthread_mutex_unlock(&philo->data->printf);
	return (0);
}

int fork_in_use(t_philo *philo)
{
	t_fork	*forks;
	int		id;
	int		count;

	forks = philo->data->forks;
	id = philo->id;
	count = philo->data->philo_count;
	if (forks[philo->id].beeing_used == 1
			|| forks[(id + 1) % count].beeing_used == 1)
		return (1);
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
	while (fork_in_use(philo))
		;
	forks[id].beeing_used = 1;
	forks[(id + 1) % count].beeing_used = 1;
	if (pthread_mutex_lock(&(forks[id].fork)) != 0)
		return (print_error(ERR_MUTEX_LOCK));
	if (pthread_mutex_lock(&(forks[(id + 1) % count].fork)) != 0)
		return (print_error(ERR_MUTEX));
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
	if (pthread_mutex_unlock(&(philo->data->forks[id].fork)) != 0)
		return (print_error(ERR_MUTEX_UNLOCK));
	if (pthread_mutex_unlock(&(philo->data->forks[(id + 1) % count].fork)) != 0)
		return (print_error(ERR_MUTEX_UNLOCK));
	philo->data->forks[id].beeing_used = 0;
	philo->data->forks[(id + 1) % count].beeing_used = 0;
	return (0);
}

int	eat(t_philo *philo)
{
	if (take_forks(philo))
		return (1);
	if (print_status(philo, EATING))
		return (1);
	usleep(philo->data->eat_time * 1000);
	if (let_forks(philo))
		return (1);
	philo->meal_count++;
	philo->last_meal = get_time_ms();
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
