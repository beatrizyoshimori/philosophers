/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:41:18 by byoshimo          #+#    #+#             */
/*   Updated: 2023/04/22 19:13:58 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	get_forks(t_philo **philo)
{
	if ((*philo)->id % 2 == 1)
	{
		pthread_mutex_lock((*philo)->left_fork);
		print_state(*philo, "has taken a fork");
		pthread_mutex_lock((*philo)->right_fork);
		print_state(*philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock((*philo)->right_fork);
		print_state(*philo, "has taken a fork");
		pthread_mutex_lock((*philo)->left_fork);
		print_state(*philo, "has taken a fork");
	}
}

static void	eat(t_philo **philo)
{
	get_forks(philo);
	if (dinner_is_over(*philo))
	{
		pthread_mutex_unlock((*philo)->right_fork);
		pthread_mutex_unlock((*philo)->left_fork);
		return ;
	}
	print_state(*philo, "is eating");
	set_last_meal(*philo);
	// usleep((*philo)->data->time_to_eat * 1000);
	msleep((*philo)->data->time_to_eat);
	pthread_mutex_unlock((*philo)->left_fork);
	pthread_mutex_unlock((*philo)->right_fork);
	set_meals(*philo);
}

static void	sleep_and_think(t_philo *philo)
{
	print_state(philo, "is sleeping");
	msleep(philo->data->time_to_sleep);
	print_state(philo, "is thinking");
	usleep(500);
}

void	*dinner(void *philo)
{
	t_philo	*tmp;

	tmp = (t_philo *)philo;
	if (tmp->id % 2 == 0)
		usleep(5);
	if (tmp->data->num_philo == 1)
	{
		pthread_mutex_lock(tmp->right_fork);
		print_state(tmp, "has taken a fork");
		pthread_mutex_unlock(tmp->right_fork);
		return (NULL);
	}
	while (!dinner_is_over(tmp))
	{
		eat(&tmp);
		if (get_meals(tmp) == tmp->data->num_times_to_eat)
			return (NULL);
		sleep_and_think(tmp);
	}
	return (NULL);
}
