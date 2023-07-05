/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 19:00:06 by byoshimo          #+#    #+#             */
/*   Updated: 2023/07/04 21:44:07 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	free_all(t_philo *philo)
{
	sem_close(philo->data->forks);
	sem_close(philo->data->print_sem);
	sem_unlink("forks_sem");
	sem_unlink("print_sem");
	free(philo->data->pid);
	free(philo->data);
	free(philo);
}

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
