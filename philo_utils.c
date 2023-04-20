/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:05:36 by byoshimo          #+#    #+#             */
/*   Updated: 2023/04/19 20:32:59 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(t_philo *philo, char *state)
{
	pthread_mutex_lock(&philo->data->printf_mutex);
	if (!check_if_died(philo))
		printf("%ld %d %s\n", get_current_time(philo->data), philo->id, state);
	pthread_mutex_unlock(&philo->data->printf_mutex);
}

int	check_if_died(t_philo *philo)
{
	if (philo->data->first_death)
		return (1);
	if (get_current_time(philo->data) - philo->time_since_last_meal
		< philo->data->time_to_die)
		return (0);
	return (1);
}

time_t	get_current_time(t_data *data)
{
	struct timeval	current_time;
	time_t			time_ms;

	gettimeofday(&current_time, NULL);
	time_ms = (current_time.tv_sec * 1000 + current_time.tv_usec / 1000)
		- data->start_time;
	return (time_ms);
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
