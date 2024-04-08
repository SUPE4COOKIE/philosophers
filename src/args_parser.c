/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 22:04:01 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/04/08 20:19:04 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include "../includes/errors.h"

ssize_t	parse_args(int ac, char **av, t_table *t)
{
	if (ac < 5 || ac > 6)
		return (print_error(ARGS_NB));
	t->philo_count = ft_atoi(av[1]);
	t->die_time = ft_atoi(av[2]);
	t->eat_time = ft_atoi(av[3]);
	t->sleep_time = ft_atoi(av[4]);
	if (ac == 6)
		t->eat_count = ft_atoi(av[5]);
	else
		t->eat_count = -1;
	if (t->philo_count < 2)
		return (print_error(PHILO_NB));
	if (t->die_time <= 0)
		return (print_error(DIE_TIME));
	if (t->eat_time <= 0)
		return (print_error(EAT_TIME));
	if (t->sleep_time <= 0)
		return (print_error(SLEEP_TIME));
	if (ac == 6 && t->eat_count < 1)
		return (print_error(EAT_COUNT));
	return (0);
}
