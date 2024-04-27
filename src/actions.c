/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:03:17 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/04/27 18:12:06 by mwojtasi         ###   ########.fr       */
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
	if (pthread_mutex_lock(&(forks[(id + 1) % count])) != 0)
		return (print_error(ERR_MUTEX));
	if (pthread_mutex_lock(&(forks[id])) != 0)
		return (print_error(ERR_MUTEX_LOCK));
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

long	get_time(void)
{
	struct timeval	tv;
	long			end;

	gettimeofday(&tv, NULL);
	end = ((tv.tv_sec * 1000) + tv.tv_usec / 1000);
	return (end);
}

void	ft_sleep(long long time)
{
	long long	start;

	start = get_time_ms();
	while (get_time_ms() < (long long)(start + time))
		usleep(100);
}