/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:05:36 by byoshimo          #+#    #+#             */
/*   Updated: 2023/04/22 19:17:02 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dinner_is_over(t_philo *philo)
{
	int	dinner_is_over;

	pthread_mutex_lock(&philo->data->dinner_mutex);
	dinner_is_over = 0;
	if (philo->data->dinner_is_over)
		dinner_is_over = philo->data->dinner_is_over;
	pthread_mutex_unlock(&philo->data->dinner_mutex);
	return (dinner_is_over);
}

void	print_state(t_philo *philo, char *state)
{
	long	current_time;

	pthread_mutex_lock(&philo->data->printf_mutex);
	current_time = timenow(philo->data->start_time);
	if (!dinner_is_over(philo))
		printf("%ld %d %s\n", current_time, philo->id, state);
	pthread_mutex_unlock(&philo->data->printf_mutex);
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

// int	get_first_death(t_philo *philo)
// {
// 	int	death;

// 	death = 0;
// 	pthread_mutex_lock(&philo->data->getter_mutex);
// 	death = philo->data->first_death;
// 	pthread_mutex_unlock(&philo->data->getter_mutex);
// 	return (death);
// }

// int	check_if_died(t_philo *philo)
// {
// 	if (get_first_death(philo))
// 		return (1);
// 	if (get_current_time(philo->data) - philo->time_since_last_meal
// 		< philo->data->time_to_die)
// 		return (0);
// 	return (1);
// }

// void	philo_died(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->data->death_mutex);
// 	if (!get_first_death(philo))
// 	{
// 		pthread_mutex_lock(&philo->data->printf_mutex);
// 		printf("%ld %d died\n", get_current_time(philo->data), philo->id);
// 		pthread_mutex_unlock(&philo->data->printf_mutex);
// 	}
// 	philo->data->first_death = 1;
// 	pthread_mutex_unlock(&philo->data->death_mutex);
// }