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
	ft_sleep(philo->data->eat_time);
	if (let_forks(philo))
		return (1);
	return (0);
}

__attribute__((hot)) int	sleep_philo(t_philo *philo)
{
	if (print_status(philo, SLEEPING))
		return (1);
	ft_sleep(philo->data->sleep_time);
	return (0);
}

 __attribute__((hot)) int	think(t_philo *philo)
{
	if (print_status(philo, THINKING))
		return (1);
	usleep(10);
	return (0);
}
