/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:02:41 by byoshimo          #+#    #+#             */
/*   Updated: 2023/07/13 21:35:32 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	check_args(int argc)
{
	if (argc < 5 || argc > 6)
	{
		printf("Wrong arguments!\nUsage:\n./philo number_of_philosophers");
		printf(" time_to_die time_to_eat time_to_sleep ");
		printf("[number_of_times_each_philosopher_must_eat]\n");
		exit(1);
	}
}

static void	kill_child_processes(t_data *data)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < data->num_philo)
	{
		pid = data->pid[i];
		kill(pid, SIGKILL);
		i++;
	}
}

static void	start_processes(t_data *data)
{
	int	i;
	int	exit_status;

	i = 0;
	while (i < data->num_philo)
	{
		data->pid[i] = fork();
		data->curr_philo = i;
		if (data->pid[i] == 0)
			dinner(data);
		i++;
	}
	exit_status = 0;
	i = 0;
	while (i < data->num_philo && exit_status == 0)
	{
		waitpid(-1, &exit_status, 0);
		exit_status = WEXITSTATUS(exit_status);
		i++;
	}
	if (exit_status == 1)
		kill_child_processes(data);
}

int	main(int argc, char *argv[])
{
	t_data	*data;
	t_philo	*philo;

	check_args(argc);
	get_data(argc, argv, &data);
	init_philos(&data, &philo);
	init_semaphores(data);
	start_processes(data);
	free_all(data);
}
