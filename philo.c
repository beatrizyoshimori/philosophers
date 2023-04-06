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

void	*routine(void *data)
{
	t_data	*tmp = (t_data *)data;
	printf("Oi %d!\n", tmp->num_philo);
}

void	create_thread(t_data *data)
{
	pthread_t	th[data->num_philo];
	int			i;
	// int			*arg;

	i = 0;
	while (i < data->num_philo)
	{
		// arg = malloc(sizeof(int));
		// *arg = i;
		if (pthread_create(&th[i], NULL, &routine, data) != 0)
			printf("Failed to create thread.\n");
		i++;
	}
	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_join(th[i], NULL) != 0)
			printf("Failed to join thread.\n");
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_data		*data;

	get_data(argc, argv, &data);
	create_thread(data);
}