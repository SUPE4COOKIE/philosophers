/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:03:17 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/09/03 02:39:10 by mwojtasi         ###   ########.fr       */
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
	ft_sleep(philo->data->eat_time, philo->data);
	philo->meal_count++;
	if (let_forks(philo))
		return (1);
	return (0);
}

__attribute__((hot)) int	sleep_philo(t_philo *philo)
{
	if (print_status(philo, SLEEPING))
		return (1);
	ft_sleep(philo->data->sleep_time, philo->data);
	return (0);
}

__attribute__((hot)) int	think(t_philo *philo)
{
	if (print_status(philo, THINKING))
		return (1);
	if (philo->data->philo_count == 3
		&& philo->data->eat_time > philo->data->sleep_time)
	{
		ft_sleep(philo->data->eat_time, philo->data);
	}
	else if ((philo->id == 0 || (philo->id == philo->data->philo_count - 2))
		&& philo->meal_count == 1 && (philo->data->philo_count % 2)
		&& (philo->data->eat_time > philo->data->sleep_time))
	{
		ft_sleep(philo->data->eat_time, philo->data);
	}
	else
		usleep(250);
	return (0);
}
