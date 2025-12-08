/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loasaad <loasaad@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 14:56:47 by loasaad           #+#    #+#             */
/*   Updated: 2025/12/08 15:00:46 by loasaad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_mutexes(t_table *table)
{
	t_fork	*forks;
	int		i;

	forks = malloc(table->philo_count * sizeof(t_fork));
	if (!forks)
		perror_exit("Error: you won't believe this but malloc failed!");
	table->forks = forks;
	i = 0;
	while (i < table->philo_count)
	{
		pthread_mutex_init(&forks[i].fork_mtx, NULL);
		forks[i].fork_id = i;
		i++;
	}
	pthread_mutex_init(&(table->mutex_print), NULL);
	pthread_mutex_init(&(table->mutex_sim), NULL);
}

void	init_data(t_table *table)
{
	t_philo	*philos;
	int		i;

	init_mutexes(table);
	philos = malloc(table->philo_count * sizeof(t_philo));
	if (!philos)
	{
		cleanup_error(table);
		perror_exit("Error: you won't believe this but malloc failed!");
	}
	table->philos = philos;
	table->sim_ended = 0;
	table->sim_start_time = 0;
	i = 0;
	while (i < table->philo_count)
	{
		philos[i].id = i + 1;
		philos[i].table = table;
		philos[i].meals_eaten = 0;
		philos[i].last_meal = 0;
		philos[i].fork_right = &(table->forks[i]);
		philos[i].fork_left = &(table->forks[(i + 1) % table->philo_count]);
		i++;
	}
}
