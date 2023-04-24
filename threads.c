/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:27:41 by byoshimo          #+#    #+#             */
/*   Updated: 2023/04/22 18:42:53 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_thread(t_philo *philo)
{
	pthread_t	*th;
	int			i;
	pthread_t	monitor;

	th = malloc(philo->data->num_philo * sizeof(pthread_t));
	i = 0;
	while (i < philo->data->num_philo)
	{
		if (pthread_create(&th[i], NULL, &dinner, &philo[i]) != 0)
			printf("Failed to create thread.\n");
		i++;
	}
	if (pthread_create(&monitor, NULL, &monitoring, philo) != 0)
		printf("Failed to create monitor thread.\n");
	i = 0;
	while (i < philo->data->num_philo)
	{
		if (pthread_join(th[i++], NULL) != 0)
			printf("Failed to join thread.\n");
	}
	if (pthread_join(monitor, NULL) != 0)
		printf("Failed to join monitor thread.\n");
	free(th);
}

void	mutexes_init(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&data->printf_mutex, NULL) != 0)
		printf("Failed to init printf mutex.\n");
	if (pthread_mutex_init(&data->meal_mutex, NULL) != 0)
		printf("Failed to init meal mutex\n");
	if (pthread_mutex_init(&data->dinner_mutex, NULL) != 0)
		printf("Failed to init dinner mutex\n");
	if (pthread_mutex_init(&data->num_meals_mutex, NULL) != 0)
		printf("Failed to init number of meals mutex\n");
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
	if (pthread_mutex_destroy(&data->meal_mutex) != 0)
		printf("Failed to destroy meal mutex.\n");
	if (pthread_mutex_destroy(&data->dinner_mutex) != 0)
		printf("Failed to destroy dinner mutex.\n");
	if (pthread_mutex_destroy(&data->num_meals_mutex) != 0)
		printf("Failed to destroy number of meals mutex.\n");
	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_mutex_destroy(&data->forks[i++]) != 0)
			printf("Failed to destroy fork mutex.\n");
	}
}
