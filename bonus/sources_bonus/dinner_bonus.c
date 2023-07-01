/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 18:55:22 by byoshimo          #+#    #+#             */
/*   Updated: 2023/07/01 19:05:23 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	philo_died(t_philo *philo)
{
	long	current_time;

	usleep(philo->data->time_to_die * 1000);
	sem_wait(philo->data->print_sem);
	current_time = timenow(philo->data->start_time);
	printf("%ld %d died\n", current_time, philo->id);
	sem_close(philo->data->forks);
	sem_close(philo->data->print_sem);
	sem_unlink("Forks");
	sem_unlink("Print");
	free(philo->data->pid);
	free(philo->data);
	free(philo);
	exit(1);
}

static void	get_forks(t_philo *philo)
{
	sem_wait(philo->data->forks);
	sem_wait(philo->data->forks);
	print_state(philo, "has taken a fork");
	print_state(philo, "has taken a fork");
}

static void	eat(t_philo **philo)
{
	long	curr_time;

	get_forks(*philo);
	// if (dinner_is_over(*philo))
	// {
	// 	pthread_mutex_unlock((*philo)->right_fork);
	// 	pthread_mutex_unlock((*philo)->left_fork);
	// 	return ;
	// }
	print_state(*philo, "is eating");
	curr_time = timenow((*philo)->data->start_time);
	// (*philo)->time_since_last_meal + (*philo)->data->time_to_eat > (*philo)->data->time_to_die
	if (curr_time + (*philo)->data->time_to_eat > (*philo)->data->time_to_die + (*philo)->time_since_last_meal)
		philo_died(*philo);
	(*philo)->time_since_last_meal = timenow((*philo)->data->start_time);
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
	if (curr_time + philo->data->time_to_eat > philo->data->time_to_die + philo->time_since_last_meal)
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
		return (NULL);
	}
	while (1)
	{
		eat(&philo);
		if (philo->num_meals == philo->data->num_times_to_eat)
			return (NULL);
		check_if_died(philo);
		sleep_and_think(philo);
	}
	// if (philo->id % 2 == 0)
	// 	usleep(8000);
	return (NULL);
}
