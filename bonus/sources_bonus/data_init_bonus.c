/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 20:56:13 by byoshimo          #+#    #+#             */
/*   Updated: 2023/06/26 21:16:29 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.c"

void	init_philos(t_data *data, t_philo **philo)
{
	int	i;

	(*philo) = (t_philo *)malloc(sizeof(t_philo) * data->num_philo);
	if (!(*philo))
	{
		printf("Failed to alloc philosophers.\n");
		// free(data->forks);
		free(data);
		exit(1);
	}
	i = 0;
	while (i < data->num_philo)
	{
		(*philo)[i].data = data;
		(*philo)[i].id = i + 1;
		(*philo)[i].time_since_last_meal = 0;
		(*philo)[i].num_meals = 0;
		i++;
	}
}

void	get_data(int argc, char *argv[], t_data **data)
{
	(*data) = (t_data *)malloc(sizeof(t_data));
	if (!(*data))
	{
		printf("Failed to alloc data.\n");
		exit(1);
	}
	(*data)->num_philo = ft_atoi(argv[1]);
	(*data)->time_to_die = ft_atoi(argv[2]);
	(*data)->time_to_eat = ft_atoi(argv[3]);
	(*data)->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		(*data)->num_times_to_eat = ft_atoi(argv[5]);
	else
		(*data)->num_times_to_eat = -1;
	(*data)->dinner_is_over = 0;
	(*data)->start_time = timestamp();
	// (*data)->forks = malloc((*data)->num_philo * sizeof(pthread_mutex_t));
}