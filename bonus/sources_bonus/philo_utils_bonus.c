/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 19:00:06 by byoshimo          #+#    #+#             */
/*   Updated: 2023/07/10 17:51:26 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	free_all(t_data *data)
{
	sem_close(data->forks);
	sem_close(data->print_sem);
	sem_unlink("forks_sem");
	sem_unlink("print_sem");
	free(data->pid);
	free(data->philos);
	free(data);
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
