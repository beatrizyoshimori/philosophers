/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:29:54 by byoshimo          #+#    #+#             */
/*   Updated: 2023/06/26 18:45:14 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	get_meals(t_philo *philo)
{
	int	meals;

	pthread_mutex_lock(&philo->data->num_meals_mutex);
	meals = philo->num_meals;
	pthread_mutex_unlock(&philo->data->num_meals_mutex);
	return (meals);
}

void	set_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->num_meals_mutex);
	philo->num_meals++;
	pthread_mutex_unlock(&philo->data->num_meals_mutex);
}

int	get_last_meal(t_philo *philo)
{
	int	last_meal;

	pthread_mutex_lock(&philo->data->meal_mutex);
	last_meal = philo->time_since_last_meal;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	return (last_meal);
}

void	set_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->time_since_last_meal = timenow(philo->data->start_time);
	pthread_mutex_unlock(&philo->data->meal_mutex);
}
