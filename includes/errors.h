/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 22:31:20 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/04/27 19:55:47 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H
# define ERR_MALLOC "Malloc failed"
# define ERR_THREAD "Thread creation failed"
# define ERR_MUTEX "Mutex initialization failed"
# define ERR_JOIN "Thread join failed"
# define ERR_MUTEX_LOCK "Mutex lock failed"
# define ERR_MUTEX_UNLOCK "Mutex unlock failed"
# define ERR_TIME "Time failed"
# define ERR_PRINTF "Printf failed"
# define ERR_USLEEP "Usleep failed"
# define PHILO_NB "Number of philosophers must be greater than 0"
# define DIE_TIME "Time to die must be greater than 0"
# define EAT_TIME "Time to eat must be greater than 0"
# define SLEEP_TIME "Time to sleep must be greater than 0"
# define EAT_COUNT "Number of times each philosopher must eat must be > than 0"
# define ARGS_NB "Wrong number of arguments"
#endif