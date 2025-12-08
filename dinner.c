/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loasaad <loasaad@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 14:56:43 by loasaad           #+#    #+#             */
/*   Updated: 2025/12/08 15:00:23 by loasaad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	pick_up_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&(philo->fork_right->fork_mtx));
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&(philo->fork_left->fork_mtx));
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&(philo->fork_left->fork_mtx));
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&(philo->fork_right->fork_mtx));
		print_status(philo, "has taken a fork");
	}
}

static void	ft_sleep(long milliseconds, t_philo *philo)
{
	long	end;

	end = get_time() + milliseconds;
	while (get_time() < end)
	{
		if (simulation_ended(philo))
			return ;
		usleep(200);
	}
}

static void	think(t_philo *p)
{
	long	t_think;

	if (p->table->philo_count % 2 == 1)
	{
		t_think = (p->table->time_to_eat * 2) - p->table->time_to_sleep;
		if (t_think < 0)
			t_think = 0;
		print_status(p, "is thinking");
		ft_sleep(t_think / 2, p);
	}
	else
		print_status(p, "is thinking");
}

static void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!simulation_ended(philo))
	{
		pick_up_forks(philo);
		print_status(philo, "is eating");
		philo->last_meal = get_time();
		ft_sleep(philo->table->time_to_eat, philo);
		philo->meals_eaten++;
		pthread_mutex_unlock(&(philo->fork_right->fork_mtx));
		pthread_mutex_unlock(&(philo->fork_left->fork_mtx));
		print_status(philo, "is sleeping");
		ft_sleep(philo->table->time_to_sleep, philo);
		think(philo);
		ft_sleep(1, philo);
	}
	return (NULL);
}

void	dinner_time(t_table *t)
{
	int			i;
	pthread_t	monitor;

	t->sim_start_time = get_time();
	i = 0;
	while (i < t->philo_count)
		t->philos[i++].last_meal = t->sim_start_time;
	i = 0;
	while (i < t->philo_count)
	{
		pthread_create(&t->philos[i].thread_id, NULL, &routine, &t->philos[i]);
		i++;
	}
	pthread_create(&monitor, NULL, &monitor_routine, t);
	i = 0;
	while (i < t->philo_count)
		pthread_join(t->philos[i++].thread_id, NULL);
	pthread_join(monitor, NULL);
}
