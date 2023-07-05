/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 18:55:22 by byoshimo          #+#    #+#             */
/*   Updated: 2023/07/04 21:53:20 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	philo_died(t_philo *philo)
{
	long	current_time;

	usleep(philo->data->time_to_die * 1000);
	sem_wait(philo->data->print_sem);
	current_time = timenow(philo->data->start_time);
	printf("%ld %d died\n", current_time, philo->id);
	free_all(philo);
	exit(1);
}

static void	eat(t_philo **philo)
{
	long	curr_time;

	sem_wait((*philo)->data->forks);
	sem_wait((*philo)->data->forks);
	print_state(*philo, "has taken a fork");
	print_state(*philo, "has taken a fork");
	print_state(*philo, "is eating");
	curr_time = timenow((*philo)->data->start_time);
	if (curr_time + (*philo)->data->time_to_eat
		> (*philo)->data->time_to_die + (*philo)->time_since_last_meal)
		philo_died(*philo);
	(*philo)->time_since_last_meal = curr_time;
	usleep((*philo)->data->time_to_eat * 1000);
	sem_post((*philo)->data->forks);
	sem_post((*philo)->data->forks);
	(*philo)->num_meals++;
}

static void	sleep_and_think(t_philo *philo)
{
	long	curr_time;

	curr_time = timenow(philo->data->start_time);
	print_state(philo, "is sleeping");
	if (curr_time + philo->data->time_to_eat
		> philo->data->time_to_die + philo->time_since_last_meal)
		philo_died(philo);
	usleep(philo->data->time_to_sleep * 1000);
	print_state(philo, "is thinking");
	usleep(500);
}

void	*dinner(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(5000);
	if (philo->data->num_philo == 1)
	{
		sem_wait(philo->data->forks);
		print_state(philo, "has taken a fork");
		sem_post(philo->data->forks);
		philo_died(philo);
	}
	while (1)
	{
		eat(&philo);
		if (philo->num_meals == philo->data->num_times_to_eat)
			break ;
		sleep_and_think(philo);
	}
	free_all(philo);
	exit(0);
}
