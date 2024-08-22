/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:03:17 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/05/05 02:23:59 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include "../includes/errors.h"
#include "../includes/actions.h"

__attribute__((hot)) long long get_sleep_time(t_philo *philo, long long time)
{
	if (get_time_ms() - philo->last_meal + time > philo->data->die_time)
		return (philo->data->die_time - (get_time_ms() - philo->last_meal) + 10);
	return (time);
}

__attribute__((hot)) int	eat(t_philo *philo)
{
	if (take_forks(philo))
		return (1);
	if (philo->data->has_started == 0)
		return (let_forks(philo));
	philo->last_meal = get_time_ms();
	if (print_status(philo, EATING))
		return (1);
	philo->meal_count++;
	ft_sleep(get_sleep_time(philo, philo->data->eat_time));
	if (let_forks(philo))
		return (1);
	return (0);
}

__attribute__((hot)) int	sleep_philo(t_philo *philo)
{
	if (print_status(philo, SLEEPING))
		return (1);
	ft_sleep(get_sleep_time(philo, philo->data->sleep_time));
	return (0);
}

 __attribute__((hot)) int	think(t_philo *philo)
{
	int philo_count;

	philo_count = philo->data->philo_count;
	if (print_status(philo, THINKING))
		return (1);
	usleep(100);
	return (0);
}
