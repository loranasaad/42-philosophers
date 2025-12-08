/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loasaad <loasaad@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 14:57:05 by loasaad           #+#    #+#             */
/*   Updated: 2025/12/08 15:40:28 by loasaad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*lone_philosopher(t_philo *philo)
{
	pthread_mutex_lock(&(philo->fork_left->fork_mtx));
	print_status(philo, "has taken a fork");
	ft_sleep(philo->table->time_to_die, philo);
	pthread_mutex_unlock(&(philo->fork_left->fork_mtx));
	return (NULL);
}

void	perror_exit(const char *message)
{
	printf("%s\n", message);
	exit(EXIT_FAILURE);
}

void	print_status(t_philo *philo, char *message)
{
	long	time;

	if (simulation_ended(philo))
		return ;
	pthread_mutex_lock(&philo->table->mutex_print);
	time = get_time() - philo->table->sim_start_time;
	printf("%ld %d %s\n", time, philo->id, message);
	pthread_mutex_unlock(&philo->table->mutex_print);
}

int	simulation_ended(t_philo *philo)
{
	int	sim_ended;

	pthread_mutex_lock(&(philo->table->mutex_sim));
	sim_ended = philo->table->sim_ended;
	pthread_mutex_unlock(&(philo->table->mutex_sim));
	return (sim_ended);
}

long	get_time(void)
{
	struct timeval	timeval;
	long			time;

	gettimeofday(&timeval, NULL);
	time = ((timeval.tv_sec) * 1000) + ((timeval.tv_usec) / 1000);
	return (time);
}
