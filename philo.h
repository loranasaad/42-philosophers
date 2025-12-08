/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loasaad <loasaad@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 14:57:02 by loasaad           #+#    #+#             */
/*   Updated: 2025/12/08 15:42:12 by loasaad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;
typedef struct s_fork
{
	t_mtx	fork_mtx;
	int		fork_id;
}			t_fork;
typedef struct s_philo
{
	int			id;
	pthread_t	thread_id;
	t_fork		*fork_left;
	t_fork		*fork_right;
	int			meals_eaten;
	long		last_meal;
	t_table		*table;
}				t_philo;
struct s_table
{
	int		philo_count;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	meal_limit;
	long	sim_start_time;
	int		sim_ended;
	t_fork	*forks;
	t_philo	*philos;
	t_mtx	mutex_print;
	t_mtx	mutex_sim;
};
void	perror_exit(const char *message);
void	print_status(t_philo *philo, char *message);
long	get_time(void);
int		simulation_ended(t_philo *philo);
void	parse_input(char **argv, t_table *table);
void	dinner_time(t_table *t);
void	init_data(t_table *table);
void	*monitor_routine(void *arg);
void	cleanup(t_table *t);
void	cleanup_error(t_table *t);
void	*lone_philosopher(t_philo *philo);
void	ft_sleep(long milliseconds, t_philo *philo);
#endif