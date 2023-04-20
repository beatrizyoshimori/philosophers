/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:27:41 by byoshimo          #+#    #+#             */
/*   Updated: 2023/04/19 21:41:49 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	*monitoring(void *data)
// {
// 	t_data	*tmp;

// 	tmp = (t_data *)data;
// 	while (1)
// 	{
		
// 	}
// }

void	create_thread(t_data *data)
{
	pthread_t	*th;
	int			i;
	t_philo		*philo;
	// pthread_t	monitor;

	// if (pthread_create(&monitor, NULL, &monitoring, data) != 0)
	// 	printf("Failed to create monitor thread.\n");
	th = malloc(data->num_philo * sizeof(pthread_t));
	i = 0;
	while (i < data->num_philo)
	{
		get_philo_info(data, &philo, i);
		if (pthread_create(&th[i++], NULL, &dinner, philo) != 0)
			printf("Failed to create thread.\n");
	}
	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_join(th[i++], NULL) != 0)
			printf("Failed to join thread.\n");
	}
	free(th);
}

void	mutexes_init(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&data->printf_mutex, NULL) != 0)
		printf("Failed to init printf mutex.\n");
	if (pthread_mutex_init(&data->death_mutex, NULL) != 0)
		printf("Failed to init death mutex\n");
	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_mutex_init(&data->forks[i++], NULL) != 0)
			printf("Failed to init fork mutex.\n");
	}
}

void	destroy_mutexes(t_data *data)
{
	int	i;

	if (pthread_mutex_destroy(&data->printf_mutex) != 0)
		printf("Failed to destroy printf mutex.\n");
	if (pthread_mutex_destroy(&data->death_mutex) != 0)
		printf("Failed to destroy death mutex.\n");
	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_mutex_destroy(&data->forks[i++]) != 0)
			printf("Failed to destroy fork mutex.\n");
	}
}
