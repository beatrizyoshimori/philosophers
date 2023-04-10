/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:47:51 by byoshimo          #+#    #+#             */
/*   Updated: 2023/04/06 20:39:56 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_thread(t_data *data)
{
	pthread_t	th[data->num_philo];
	int			i;
	t_philo		*philo;

	i = 0;
	while (i < data->num_philo)
	{
		get_philo_info(data, &philo, i);
		if (pthread_create(&th[i++], NULL, &dinner, philo) != 0)
			printf("Failed to create thread.\n");
	}
	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_join(th[i++], NULL) != 0)
			printf("Failed to join thread.\n");
	}
}

int	main(int argc, char *argv[])
{
	t_data		*data;

	check_args(argc);
	get_data(argc, argv, &data);
	mutexes_init(data);
	create_thread(data);
	destroy_mutexes(data);
}