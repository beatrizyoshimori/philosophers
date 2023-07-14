/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 21:32:55 by byoshimo          #+#    #+#             */
/*   Updated: 2023/07/13 21:32:57 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	check_if_died(t_data *data)
{
	long	curr_time;

	curr_time = timenow(data->start_time);
	if ((curr_time - data->philos[data->curr_philo].time_since_last_meal)
		> data->time_to_die)
	{
		sem_wait(data->print_sem);
		curr_time = timenow(data->start_time);
		printf("%ld %d died\n", curr_time,
			data->philos[data->curr_philo].id);
		free_all(data);
		exit(1);
	}
}

void	wait_for_fork(t_data *data)
{
	while (*(long *)(data->forks) < 2)
	{
		check_if_died(data);
		usleep(10);
	}
}

void	action_time(t_data *data, long time)
{
	long	start_time;

	start_time = timestamp();
	while (timestamp() - start_time < time)
	{
		usleep(10);
		check_if_died(data);
	}
}
