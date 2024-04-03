/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 20:35:37 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/04/03 22:42:02 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/imports.h"
#include "../includes/structs.h"

int	main(int ac, char **av)
{
	t_table	data;

	if (parse_args(ac, av, &data) != 0)
		return (1);
}
