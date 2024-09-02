/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 19:23:06 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/05/05 02:34:46 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include "../includes/errors.h"

long long	get_time_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (print_error(ERR_TIME), -1);
	return ((long long)((time.tv_sec * 1000) + (time.tv_usec / 1000)));
}

long	get_time(void)
{
	struct timeval	tv;
	long			end;

	gettimeofday(&tv, NULL);
	end = ((tv.tv_sec * 1000) + tv.tv_usec / 1000);
	return (end);
}

__attribute__((hot)) void	ft_sleep(long long time, _Atomic char *has_started)
{
	long long	start;

	start = get_time_ms();
	while (get_time_ms() < (long long)(start + time))
	{
		if (*has_started != 1)
			return ;
		usleep(100);
	}
}
