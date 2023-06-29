/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 18:55:22 by byoshimo          #+#    #+#             */
/*   Updated: 2023/06/28 21:33:10 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	check_if_died(t_philo *philo)
{
	int	current_time;

	current_time = timenow(philo->data->start_time);
	if ((current_time - get_last_meal(philo)) > philo->data->time_to_die)
	{
		
		exit(1);
	}
	return ;
}

static void	get_forks(t_philo *philo)
{
	sem_wait(philo->data->forks);
	print_state(philo, "has taken a fork");
	sem_wait(philo->data->forks);
	print_state(philo, "has taken a fork");
}

static void	eat(t_philo **philo)
{
	get_forks(*philo);
	// if (dinner_is_over(*philo))
	// {
	// 	pthread_mutex_unlock((*philo)->right_fork);
	// 	pthread_mutex_unlock((*philo)->left_fork);
	// 	return ;
	// }
	print_state(*philo, "is eating");
	set_last_meal(*philo);
	usleep((*philo)->data->time_to_eat * 1000);
	sem_post((*philo)->data->forks);
	sem_post((*philo)->data->forks);
	set_meals(*philo);
}

static void	sleep_and_think(t_philo *philo)
{
	print_state(philo, "is sleeping");
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
	while (philo->num_meals < philo->data->num_times_to_eat)
	{
		check_if_died(philo);
		eat(&philo);
		if (get_meals(philo) == philo->data->num_times_to_eat)
			return (NULL);
		check_if_died(philo);
		sleep_and_think(philo);
	}
	if (philo->id % 2 == 0)
		usleep(8000);
	return (NULL);
}
