/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 19:00:06 by byoshimo          #+#    #+#             */
/*   Updated: 2023/07/01 18:16:56 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// int	dinner_is_over(t_philo *philo)
// {
// 	int	dinner_is_over;

// 	// pthread_mutex_lock(&philo->data->dinner_mutex);
// 	dinner_is_over = 0;
// 	if (philo->data->dinner_is_over)
// 		dinner_is_over = philo->data->dinner_is_over;
// 	// pthread_mutex_unlock(&philo->data->dinner_mutex);
// 	return (dinner_is_over);
// }

void	print_state(t_philo *philo, char *state)
{
	long	current_time;

	sem_wait(philo->data->print_sem);
	current_time = timenow(philo->data->start_time);
	printf("%ld %d %s\n", current_time, philo->id, state);
	sem_post(philo->data->print_sem);
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
