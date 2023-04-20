/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:47:51 by byoshimo          #+#    #+#             */
/*   Updated: 2023/04/19 21:09:34 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_args(int argc)
{
	if (argc < 5 || argc > 6)
	{
		printf("Wrong arguments!\nUsage:\n./philo number_of_philosophers");
		printf(" time_to_die time_to_eat time_to_sleep ");
		printf("[number_of_times_each_philosopher_must_eat]\n");
		exit(1);
	}
}

int	main(int argc, char *argv[])
{
	t_data		*data;

	check_args(argc);
	get_data(argc, argv, &data);
	mutexes_init(data);
	create_thread(data);
	destroy_mutexes(data);
	free(data->forks);
	free(data);
}
