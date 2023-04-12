/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:05:36 by byoshimo          #+#    #+#             */
/*   Updated: 2023/04/11 21:14:25 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(t_philo *philo, char *state)
{
	pthread_mutex_lock(&philo->data->printf_mutex);
	printf("%ld %d %s\n", get_current_time(philo->data), philo->id, state);
	pthread_mutex_unlock(&philo->data->printf_mutex);
}

time_t	get_current_time(t_data *data)
{
	struct timeval	current_time;
	time_t			time_ms;

	gettimeofday(&current_time, NULL);
	time_ms = (current_time.tv_sec * 1000 + current_time.tv_usec / 1000) - data->start_time;
	return (time_ms);
}

void	get_philo_info(t_data *data, t_philo **philo, int i)
{
	(*philo) = (t_philo *)malloc(sizeof(t_philo));
	(*philo)->data = data;
	(*philo)->id = i + 1;
	(*philo)->time_since_last_meal = 0;
	(*philo)->num_meals = 0;
	(*philo)->is_dead = 0;
	(*philo)->left_fork = &data->forks[i];
	if (i == data->num_philo - 1)
		(*philo)->right_fork = &data->forks[0];
	else
		(*philo)->right_fork = &data->forks[i + 1];
}

void	get_data(int argc, char *argv[], t_data **data)
{
	struct timeval	current_time;

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
	gettimeofday(&current_time, NULL);
	(*data)->start_time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	(*data)->forks = malloc((*data)->num_philo * sizeof(pthread_mutex_t));
}

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	num;

	sign = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	num = 0;
	while ((*nptr) >= '0' && (*nptr) <= '9')
	{
		num = num * 10 + (*nptr - 48);
		nptr++;
	}
	return (num * sign);
}
