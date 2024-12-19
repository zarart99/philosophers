/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_atcions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemii <artemii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 01:28:29 by artemii           #+#    #+#             */
/*   Updated: 2024/12/19 23:46:31 by artemii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	eat_printing(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%lld %d has taken a fork\n", current_time()
		- philo->data->start_time, philo->id);
	printf("%lld %d has taken a fork\n", current_time()
		- philo->data->start_time, philo->id);
	printf("%lld %d is eating\n", current_time() - philo->data->start_time,
		philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	philosopher_eat(t_philosopher *philo)
{
	if (!get_simulation_running(philo->data))
		return ;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	if (!get_simulation_running(philo->data))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	eat_printing(philo);
	philo->last_meal_time = current_time();
	usleep_custom(philo->data->time_to_eat, philo->data);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philosopher_sleep(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%lld %d is sleeping\n", current_time() - philo->data->start_time,
		philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	usleep_custom(philo->data->time_to_sleep, philo->data);
	if (!get_simulation_running(philo->data))
		return ;
}

void	philosopher_think(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%lld %d is thinking\n", current_time() - philo->data->start_time,
		philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	if (!get_simulation_running(philo->data))
		return ;
}
