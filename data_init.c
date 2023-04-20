/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:39:30 by byoshimo          #+#    #+#             */
/*   Updated: 2023/04/20 19:06:06 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_philo_info(t_data *data, t_philo **philo, int i)
{
	(*philo) = (t_philo *)malloc(sizeof(t_philo));
	(*philo)->data = data;
	(*philo)->id = i + 1;
	(*philo)->time_since_last_meal = 0;
	(*philo)->num_meals = 0;
	(*philo)->is_dead = 0;
	(*philo)->left_fork = &data->forks[i];
	(*philo)->right_fork = &data->forks[(i + 1) % data->num_philo];
	// if (i == data->num_philo - 1)
	// 	(*philo)->right_fork = &data->forks[0];
	// else
	// 	(*philo)->right_fork = &data->forks[i + 1];
}

void	get_data(int argc, char *argv[], t_data **data)
{
	struct timeval	curr_time;

	(*data) = (t_data *)malloc(sizeof(t_data));
	(*data)->num_philo = ft_atoi(argv[1]);
	(*data)->time_to_die = ft_atoi(argv[2]);
	(*data)->time_to_eat = ft_atoi(argv[3]);
	(*data)->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		(*data)->num_times_to_eat = ft_atoi(argv[5]);
	else
		(*data)->num_times_to_eat = -1;
	(*data)->first_death = 0;
	gettimeofday(&curr_time, NULL);
	(*data)->start_time = curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000;
	(*data)->forks = malloc((*data)->num_philo * sizeof(pthread_mutex_t));
}
