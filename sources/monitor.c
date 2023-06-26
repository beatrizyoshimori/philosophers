/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:29:43 by byoshimo          #+#    #+#             */
/*   Updated: 2023/06/26 18:45:19 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	print_death(t_philo *philo)
{
	long	current_time;

	pthread_mutex_lock(&philo->data->printf_mutex);
	current_time = timenow(philo->data->start_time);
	printf("%ld %d died\n", current_time, philo->id);
	pthread_mutex_unlock(&philo->data->printf_mutex);
}

static void	finish_dinner(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dinner_mutex);
	philo->data->dinner_is_over = 1;
	pthread_mutex_unlock(&philo->data->dinner_mutex);
}

static int	all_philos_ate(t_philo *philo)
{
	int	i;
	int	had_dinner;

	had_dinner = 0;
	i = -1;
	while (++i < philo->data->num_philo)
	{
		if (get_meals(&philo[i]) == philo[i].data->num_times_to_eat)
			had_dinner++;
	}
	if (had_dinner == philo->data->num_philo)
		return (1);
	return (0);
}

void	*monitoring(void *ptr)
{
	t_philo	*philo;
	int		current_time;
	int		time_to_die;
	int		i;

	philo = (t_philo *)ptr;
	time_to_die = philo->data->time_to_die;
	while (!all_philos_ate(philo))
	{
		i = -1;
		while (++i < philo->data->num_philo)
		{
			current_time = timenow(philo->data->start_time);
			if ((current_time - get_last_meal(&philo[i])) > time_to_die)
			{
				finish_dinner(&philo[i]);
				print_death(&philo[i]);
				return (NULL);
			}
		}
		usleep(100);
	}
	return (NULL);
}
