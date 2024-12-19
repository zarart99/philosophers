/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemii <artemii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 01:28:26 by artemii           #+#    #+#             */
/*   Updated: 2024/12/19 23:46:36 by artemii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	is_number(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	parse_positive_int(char *str)
{
	int	value;

	value = ft_atol(str);
	if (value <= 0 || value > 2147483647)
		return (-1);
	return ((int)value);
}

int	parse_args(int argc, char **argv, t_data *data)
{
	if (argc < 5 || argc > 6)
		return (-1);
	if (!is_number(argv[1]) || !is_number(argv[2]) || !is_number(argv[3])
		|| !is_number(argv[4]))
		return (-1);
	if (argc == 6 && !is_number(argv[5]))
		return (-1);
	data->num_philosophers = parse_positive_int(argv[1]);
	data->time_to_die = parse_positive_int(argv[2]);
	data->time_to_eat = parse_positive_int(argv[3]);
	data->time_to_sleep = parse_positive_int(argv[4]);
	if (argc == 6)
		data->max_meals = parse_positive_int(argv[5]);
	else
		data->max_meals = -1;
	if (data->num_philosophers <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0 || (argc == 6
			&& data->max_meals < 0))
		return (-1);
	return (0);
}
