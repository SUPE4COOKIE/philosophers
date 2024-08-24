/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 22:29:21 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/08/23 02:32:43 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include "../includes/errors.h"
#include "../includes/actions.h"

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (s[count])
		count++;
	return (count);
}

ssize_t	print_error(char *str)
{
	return (write(2, str, ft_strlen(str)));
}

__attribute__((hot)) int	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->data->printf);
	if (philo->data->has_started == 0)
		return (pthread_mutex_unlock(&philo->data->printf), 0);
	if (printf("%lld %d %s\n",
			get_time_ms() - philo->data->start_time,
			philo->id + 1,
			status) < 0)
		return (print_error(ERR_PRINTF));
	pthread_mutex_unlock(&philo->data->printf);
	return (0);
}

int	print_forks_taken(t_philo *philo)
{
	if (print_status(philo, FORK_TAKEN))
		return (1);
	if (print_status(philo, FORK_TAKEN))
		return (1);
	return (0);
}
