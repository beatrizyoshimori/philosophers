/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 18:55:22 by byoshimo          #+#    #+#             */
/*   Updated: 2023/07/10 18:46:24 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	check_if_died(t_data *data, long time)
{
	long	start_time;
	long	curr_time;

	start_time = timestamp();
	while (timestamp() - start_time < time)
	{
		usleep(10);
		curr_time = timenow(data->start_time);
		if ((curr_time - data->philos[data->curr_philo].time_since_last_meal)
			> data->time_to_die)
		{
			sem_wait(data->print_sem);
			curr_time = timenow(data->start_time);
			printf("%ld %d died\n", curr_time,
				data->philos[data->curr_philo].id);
			free_all(data);
			exit(1);
		}
	}
}

static void	eat(t_data **data)
{
	sem_wait((*data)->forks);
	sem_wait((*data)->forks);
	print_state(&(*data)->philos[(*data)->curr_philo], "has taken a fork");
	print_state(&(*data)->philos[(*data)->curr_philo], "has taken a fork");
	print_state(&(*data)->philos[(*data)->curr_philo], "is eating");
	(*data)->philos[(*data)->curr_philo].time_since_last_meal
		= timenow((*data)->start_time);
	check_if_died(*data, (*data)->time_to_eat);
	sem_post((*data)->forks);
	sem_post((*data)->forks);
	(*data)->philos[(*data)->curr_philo].num_meals++;
}

static void	sleep_and_think(t_data *data)
{
	print_state(&(data->philos[data->curr_philo]), "is sleeping");
	check_if_died(data, data->time_to_sleep);
	print_state(&(data->philos[data->curr_philo]), "is thinking");
	usleep(500);
}

void	*dinner(t_data *data)
{
	if (data->philos[data->curr_philo].id % 2 == 0)
		usleep(5000);
	if (data->num_philo == 1)
	{
		sem_wait(data->forks);
		print_state(&(data->philos[data->curr_philo]), "has taken a fork");
		sem_post(data->forks);
		usleep(data->time_to_die * 1000);
		print_state(&(data->philos[data->curr_philo]), "died");
		free_all(data);
		exit(1);
	}
	while (1)
	{
		eat(&data);
		if (data->philos[data->curr_philo].num_meals == data->num_times_to_eat)
			break ;
		sleep_and_think(data);
	}
	free_all(data);
	exit(0);
}
