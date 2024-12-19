/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemii <artemii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 01:28:18 by artemii           #+#    #+#             */
/*   Updated: 2024/12/19 23:46:40 by artemii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (parse_args(argc, argv, &data) == -1)
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
	if (init_simulation(&data) == -1)
	{
		printf("Error: Failed to initialize simulation\n");
		return (1);
	}
	start_simulation(&data);
	clean_up(&data);
	return (0);
}
