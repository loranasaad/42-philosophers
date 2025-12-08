/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loasaad <loasaad@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 14:56:37 by loasaad           #+#    #+#             */
/*   Updated: 2025/12/08 14:59:08 by loasaad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup_error(t_table *t)
{
	int	i;

	i = 0;
	while (i < t->philo_count)
		pthread_mutex_destroy(&t->forks[i++].fork_mtx);
	pthread_mutex_destroy(&t->mutex_print);
	pthread_mutex_destroy(&t->mutex_sim);
	free(t->forks);
}

void	cleanup(t_table *t)
{
	int	i;

	i = 0;
	while (i < t->philo_count)
		pthread_mutex_destroy(&t->forks[i++].fork_mtx);
	pthread_mutex_destroy(&t->mutex_print);
	pthread_mutex_destroy(&t->mutex_sim);
	free(t->forks);
	free(t->philos);
}
