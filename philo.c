/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:47:51 by byoshimo          #+#    #+#             */
/*   Updated: 2023/04/06 20:39:56 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(t_philo *philo, char *state)
{
	pthread_mutex_lock(&philo->data->printf_mutex);
	printf("%ld %d %s\n", get_current_time(philo->data), philo->id, state);
	pthread_mutex_unlock(&philo->data->printf_mutex);
}

void	eat(t_philo **philo)
{
	pthread_mutex_lock((*philo)->left_fork);
	print_state(*philo, "has taken a fork");
	pthread_mutex_lock((*philo)->right_fork);
	print_state(*philo, "has taken a fork");
	print_state(*philo, "is eating");
	(*philo)->time_since_last_meal = get_current_time((*philo)->data);
	usleep((*philo)->data->time_to_eat * 1000);
	pthread_mutex_unlock((*philo)->left_fork);
	pthread_mutex_unlock((*philo)->right_fork);
	(*philo)->num_meals++;
}

void	*routine(void *philo)
{
	t_philo	*tmp;

	tmp = (t_philo *)philo;
	while (get_current_time(tmp->data) - tmp->time_since_last_meal < tmp->data->time_to_die
		&& tmp->num_meals < tmp->data->num_times_to_eat)
	{
		eat(&tmp);
		if (get_current_time(tmp->data) - tmp->time_since_last_meal < tmp->data->time_to_die)
		{
			print_state(tmp, "is sleeping");
			usleep(tmp->data->time_to_sleep * 1000);
		}
		else
		{
			printf("%d died\n", tmp->id);
			free(philo);
			return (NULL);
		}
		if (get_current_time(tmp->data) - tmp->time_since_last_meal < tmp->data->time_to_die)
		{
			print_state(tmp, "is thinking");
		}
		else
		{
			printf("%d died\n", tmp->id);
			free(philo);
			return (NULL);
		}
	}
	free(philo);
	return (NULL);
}

void	create_thread(t_data *data)
{
	pthread_t	th[data->num_philo];
	int			i;
	t_philo		*philo;

	mutexes_init(data);
	i = 0;
	while (i < data->num_philo)
	{
		get_philo_info(data, &philo, i);
		if (pthread_create(&th[i++], NULL, &routine, philo) != 0)
			printf("Failed to create thread.\n");
	}
	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_join(th[i++], NULL) != 0)
			printf("Failed to join thread.\n");
	}
	destroy_mutexes(data);
}

int	main(int argc, char *argv[])
{
	t_data		*data;

	get_data(argc, argv, &data);
	create_thread(data);
}