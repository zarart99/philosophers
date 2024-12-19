/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemii <artemii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 01:28:33 by artemii           #+#    #+#             */
/*   Updated: 2024/12/20 02:06:21 by artemii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*philosopher_thread(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (get_simulation_running(philo->data))
	{
		philosopher_eat(philo);
		if (!get_simulation_running(philo->data))
			break ;
		philosopher_sleep(philo);
		if (!get_simulation_running(philo->data))
			break ;
		philosopher_think(philo);
	}
	return (NULL);
}

int	all_philosophers_satisfied(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		if (data->philosophers[i].meals_eaten < data->max_meals)
			return (0);
		i++;
	}
	return (1);
}

void	monitor_philosophers(t_data *data)
{
	int	i;

	while (get_simulation_running(data))
	{
		i = 0;
		while (i < data->num_philosophers)
		{
			if (current_time()
				- data->philosophers[i].last_meal_time > data->time_to_die)
			{
				pthread_mutex_lock(&data->print_mutex);
				printf("%lld %d died\n", current_time() - data->start_time,
					data->philosophers[i].id);
				pthread_mutex_unlock(&data->print_mutex);
				set_simulation_running(data, 0);
				return ;
			}
			i++;
		}
		if (data->max_meals != -1 && all_philosophers_satisfied(data))
			return (set_simulation_running(data, 0));
		usleep_custom(1, data);
	}
}

void	handle_one_philosopher(t_data *data)
{
	pthread_mutex_lock(&data->forks[0]);
	printf("%lld %d has taken a fork\n", current_time() - data->start_time, 1);
	usleep_custom(data->time_to_die, data);
	printf("%lld %d died\n", current_time() - data->start_time, 1);
	pthread_mutex_unlock(&data->forks[0]);
	set_simulation_running(data, 0);
}

void	start_simulation(t_data *data)
{
	int	i;

	if (data->num_philosophers == 1)
		return (handle_one_philosopher(data));
	i = 0;
	while (i < data->num_philosophers)
	{
		if (pthread_create(&data->philosophers[i].thread, NULL,
				philosopher_thread, &data->philosophers[i]) != 0)
		{
			printf("Error: Failed to create thread for philosopher %d\n", i
				+ 1);
			set_simulation_running(data, 0);
			return ;
		}
		i++;
	}
	monitor_philosophers(data);
	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_join(data->philosophers[i].thread, NULL);
		i++;
	}
}
