/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:02:41 by byoshimo          #+#    #+#             */
/*   Updated: 2023/06/26 21:19:56 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	start_processes(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->num_philo)
	{
		philo[i].pid = fork();
		if (philo[i].pid == 0)
		{

		}
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_data		*data;
	t_philo		*philo;

	check_args(argc);
	get_data(argc, argv, &data);
	init_philos(data, &philo);
	start_processes(philo);
}