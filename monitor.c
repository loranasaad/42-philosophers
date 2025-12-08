/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loasaad <loasaad@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 14:56:31 by loasaad           #+#    #+#             */
/*   Updated: 2025/12/08 16:30:20 by loasaad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	end_sim(t_table *t)
{
	pthread_mutex_lock(&t->mutex_sim);
	t->sim_ended = 1;
	pthread_mutex_unlock(&t->mutex_sim);
}

static int	everyone_ate_enough(t_table *t)
{
	int	i;
	int	everyone_ate;
	int	meals;

	i = 0;
	everyone_ate = 1;
	while (i < t->philo_count)
	{
		pthread_mutex_lock(&t->mutex_sim);
		meals = t->philos[i].meals_eaten;
		pthread_mutex_unlock(&t->mutex_sim);
		if (meals < t->meal_limit)
			everyone_ate = 0;
		i++;
	}
	return (everyone_ate);
}

static int	check_philos_death(t_table *t)
{
	int		i;
	long	time_since;

	i = 0;
	while (i < t->philo_count)
	{
		pthread_mutex_lock(&t->mutex_sim);
		time_since = get_time() - t->philos[i].last_meal;
		pthread_mutex_unlock(&t->mutex_sim);
		if (time_since > t->time_to_die)
		{
			print_status(&t->philos[i], "died");
			end_sim(t);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_table	*t;

	t = (t_table *)arg;
	while (!simulation_ended(&t->philos[0]))
	{
		if (check_philos_death(t))
			return (NULL);
		if (t->meal_limit != -1 && everyone_ate_enough(t))
		{
			end_sim(t);
			return (NULL);
		}
		usleep(200);
	}
	return (NULL);
}
