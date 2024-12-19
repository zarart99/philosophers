/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemii <artemii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 01:28:37 by artemii           #+#    #+#             */
/*   Updated: 2024/12/20 00:26:16 by artemii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_atol(char *str)
{
	unsigned long long int	nb;
	int						i;

	i = 0;
	nb = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (nb > 2147483647)
		return (-1);
	return ((int)nb);
}

long long	current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
	{
		printf("Error getting time");
		return (-1);
	}
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	usleep_custom(int ms, t_data *data)
{
	long long	start;

	start = current_time();
	while ((current_time() - start) < ms && data->simulation_running)
		usleep(100);
}

int	get_simulation_running(t_data *data)
{
	int	running;

	pthread_mutex_lock(&data->sim_mutex);
	running = data->simulation_running;
	pthread_mutex_unlock(&data->sim_mutex);
	return (running);
}

void	set_simulation_running(t_data *data, int value)
{
	pthread_mutex_lock(&data->sim_mutex);
	data->simulation_running = value;
	pthread_mutex_unlock(&data->sim_mutex);
}
