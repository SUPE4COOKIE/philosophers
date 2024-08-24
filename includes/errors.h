/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 02:57:56 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/08/24 02:57:58 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H
# define ERR_MALLOC "Malloc failed\n"
# define ERR_THREAD "Thread creation failed\n"
# define ERR_MUTEX "Mutex initialization failed\n"
# define ERR_JOIN "Thread join failed\n"
# define ERR_MUTEX_LOCK "Mutex lock failed\n"
# define ERR_MUTEX_UNLOCK "Mutex unlock failed\n"
# define ERR_TIME "Time failed\n"
# define ERR_PRINTF "Printf failed\n"
# define ERR_USLEEP "Usleep failed\n"
# define PHILO_NB "Invalid number of philosophers\n"
# define DIE_TIME "Invalid time to die\n"
# define EAT_TIME "Invalid time to eat\n"
# define SLEEP_TIME "Invalid time to sleep\n"
# define EAT_COUNT "Number of times each philosopher must eat is Invalid\n"
# define ARGS_NB "Wrong number of arguments\n"
#endif
