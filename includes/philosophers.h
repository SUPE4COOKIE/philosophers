/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 19:35:01 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/04/23 13:35:38 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>
# include <limits.h>

typedef struct s_philo	t_philo;
typedef struct s_fork	t_fork;

typedef struct s_table
{
	int			philo_count;
	int			die_time;
	int			eat_time;
	int			sleep_time;
	int			eat_count;
	_Atomic	char	has_started;
	_Atomic long long		start_time;
	t_philo		*philosophers;
	pthread_mutex_t	*forks;
	pthread_mutex_t	printf;
}				t_table;

struct s_philo
{
	int				id;
	_Atomic long long	last_meal;
	_Atomic char	alive;
	size_t			meal_count;
	pthread_t		thread;
	t_table			*data;
};

int		ft_atoi(const char *nptr);
ssize_t	parse_args(int ac, char **av, t_table *t);
ssize_t	print_error(char *str);
int		init_philos(t_table *table);
int		init_threads(t_table *table);
int		init_mutexes(t_table *table);
long long	get_time_ms(void);
void 	*routine(void *arg);
int		eat(t_philo *philo);
int		sleep_philo(t_philo *philo);
int		think(t_philo *philo);
int		death_giver(t_table *table);
int		print_status(t_philo *philo, char *status);
void	free_table(t_table *table);
# endif