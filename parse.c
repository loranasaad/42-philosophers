/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loasaad <loasaad@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 14:56:52 by loasaad           #+#    #+#             */
/*   Updated: 2025/12/08 15:02:00 by loasaad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

static int	is_space(char c)
{
	if ((c <= 13 && c >= 9) || c == 32)
		return (1);
	return (0);
}

static int	is_numeric(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static char	*validate_number(char *str)
{
	char	*number;
	int		len;
	int		i;

	i = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '-')
		perror_exit("Error: negative numbers are not allowed!");
	else if (str[i] == '+')
		i++;
	if (!is_numeric(str[i]))
		perror_exit("Error: invalid number!");
	number = &str[i];
	len = 0;
	while (is_numeric(str[i]))
	{
		len++;
		i++;
	}
	if (len > 10)
		perror_exit("Error: value bigger than INT_MAX");
	return (number);
}

static long	ft_atol(char *input)
{
	char	*str;
	int		number;
	int		i;

	str = validate_number(input);
	i = 0;
	number = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = (str[i] - '0') + (10 * number);
		i++;
	}
	if (number > INT_MAX)
		perror_exit("Error: value bigger than INT_MAX");
	return (number);
}

void	parse_input(char **argv, t_table *table)
{
	table->philo_count = ft_atol(argv[1]);
	if (table->philo_count == 0)
		perror_exit("Error: too few philosophers");
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		table->meal_limit = ft_atol(argv[5]);
	else
		table->meal_limit = -1;
}
