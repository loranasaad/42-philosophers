/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loasaad <loasaad@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 14:56:31 by loasaad           #+#    #+#             */
/*   Updated: 2025/12/08 14:58:02 by loasaad          ###   ########.fr       */
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

	i = 0;
	everyone_ate = 1;
	while (i < t->philo_count)
	{
		if (t->philos[i].meals_eaten < t->meal_limit)
			everyone_ate = 0;
		i++;
	}
	return (everyone_ate);
}

void	*monitor_routine(void *arg)
{
	t_table	*t;
	int		i;

	t = (t_table *)arg;
	while (!simulation_ended(&t->philos[0]))
	{
		i = 0;
		while (i < t->philo_count)
		{
			if (get_time() - t->philos[i].last_meal > t->time_to_die)
			{
				print_status(&t->philos[i], "died");
				end_sim(t);
				return (NULL);
			}
			i++;
		}
		if (t->meal_limit != -1 && everyone_ate_enough(t))
		{
			end_sim(t);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
