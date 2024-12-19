/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemii <artemii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 23:47:22 by artemii           #+#    #+#             */
/*   Updated: 2024/12/19 23:47:26 by artemii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philosopher
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long long		last_meal_time;
	int				meals_eaten;
	struct s_data	*data;
}					t_philosopher;

typedef struct s_data
{
	int				num_philosophers;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				max_meals;
	int				simulation_running;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*forks;
	t_philosopher	*philosophers;
	long long		start_time;
	pthread_mutex_t	sim_mutex;
}					t_data;

int					parse_args(int argc, char **argv, t_data *data);
int					init_simulation(t_data *data);
void				start_simulation(t_data *data);
void				clean_up(t_data *data);
long long			current_time(void);
void				usleep_custom(int ms, t_data *data);
int					ft_atol(char *str);
void				philosopher_eat(t_philosopher *philo);
void				philosopher_sleep(t_philosopher *philo);
void				philosopher_think(t_philosopher *philo);
void				*philosopher_thread(void *arg);
int					get_simulation_running(t_data *data);
void				set_simulation_running(t_data *data, int value);

#endif
