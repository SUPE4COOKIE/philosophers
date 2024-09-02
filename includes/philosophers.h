/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtasi <mwojtasi@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 19:35:01 by mwojtasi          #+#    #+#             */
/*   Updated: 2024/08/24 04:17:43 by mwojtasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>
# include <stdio.h>

typedef struct s_philo	t_philo;
typedef struct s_fork	t_fork;
typedef struct s_table	t_table;

struct			s_table
{
	_Atomic int			eat_count;
	_Atomic char		has_started;
	t_fork				*forks;
	pthread_mutex_t		printf;
	int					philo_count;
	int					die_time;
	int					eat_time;
	int					sleep_time;
	t_philo				*philosophers;
	_Atomic long long	start_time;
}	__attribute__((aligned(64)));

struct s_philo
{
	_Atomic long long	last_meal;
	_Atomic char		alive;
	_Atomic size_t		meal_count;
	pthread_t			thread;
	t_table				*data;
	int					id;
}	__attribute__((aligned(64)));

struct s_fork
{
	pthread_mutex_t	fork;
	_Atomic char	taken;
};

int			ft_atoi(const char *nptr);
ssize_t		parse_args(int ac, char **av, t_table *t);
ssize_t		print_error(char *str);
int			init_philos(t_table *table);
int			init_threads(t_table *table);
int			init_mutexes(t_table *table);
void		*routine(void *arg);
int			eat(t_philo *philo) __attribute__((hot));
int			sleep_philo(t_philo *philo) __attribute__((hot));
int			think(t_philo *philo) __attribute__((hot));
int			death_giver(t_table *table) __attribute__((hot));
int			print_status(t_philo *philo, char *status) __attribute__((hot));
long long	get_sleep_time(t_philo *philo, long long time)__attribute__((hot));
int			meal_ender(t_table *table) __attribute__((hot));
void		free_table(t_table *table);
void		ft_sleep(long long time) __attribute__((hot));
long		get_time(void);
int			all_have_eaten(t_table *table);
int			remaining_alive(t_table *table) __attribute__((hot));
long long	get_time_ms(void);
int			single_fork(t_philo *philo);
int			print_forks_taken(t_philo *philo);
void		free_forks_until_n(t_table *table, int n);
void		free_no_printf(t_table *table);
int			take_forks(t_philo *philo);
int			let_forks(t_philo *philo);
#endif