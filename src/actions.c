/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:03:17 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/04/09 22:25:19 by mwojtasi         ###   ########.fr       */
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

int	take_forks(t_philo *philo)
{
	t_fork	*forks;
	int		id;
	int		count;

	forks = philo->data->forks;
	id = philo->id;
	count = philo->data->philo_count;
	// avoid deadlock by not locking any fork if one is already in use
	while (forks[philo->id].beeing_used == 1
			|| forks[(id + 1) % count].beeing_used == 1)
		;
	if (pthread_mutex_lock(&(forks[id].fork)) != 0)
		return (print_error(ERR_MUTEX_LOCK));
	if (pthread_mutex_lock(&(forks[(id + 1) % count].fork)) != 0)
		return (print_error(ERR_MUTEX));
	forks[id].beeing_used = 1;
	forks[(id + 1) % count].beeing_used = 1;
	print_status(philo, FORK_TAKEN);
	print_status(philo, FORK_TAKEN);
	pthread_mutex_unlock(&(forks[id].fork));
	pthread_mutex_unlock(&(forks[(id + 1) % count].fork));
	return (0);
}
int	eat(t_philo *philo)
{
	if (take_forks(philo))
		return (1);
	if (print_status(philo, EATING))
		return (1);
	if (usleep(philo->data->eat_time) < 0)
		return (print_error(ERR_USLEEP));
	philo->meal_count++;
	
	philo->last_meal = get_time_ms();
	print_status(philo, "is eating");
	return (0);
}