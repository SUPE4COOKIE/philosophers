/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 19:35:01 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/04/14 09:47:42 by mwojtasi         ###   ########.fr       */
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
	t_fork		*forks;
	pthread_mutex_t	printf;
}				t_table;

struct s_philo
{
	int				id;
	int				last_meal;
	size_t			meal_count;
	pthread_t		thread;
	t_table			*data;
};

struct s_fork
{
	pthread_mutex_t			beein_checked;
	_Atomic char			beeing_used;
	pthread_mutex_t			fork;
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
# endif