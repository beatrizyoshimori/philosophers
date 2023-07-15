/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:47:51 by byoshimo          #+#    #+#             */
/*   Updated: 2023/07/14 21:20:20 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_data		*data;
	t_philo		*philo;

	check_args(argc, argv);
	get_data(argc, argv, &data);
	init_philos(data, &philo);
	mutexes_init(data);
	create_thread(philo);
	destroy_mutexes(data);
	free(data->forks);
	free(data);
	free(philo);
}
