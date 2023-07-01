/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:02:41 by byoshimo          #+#    #+#             */
/*   Updated: 2023/07/01 18:13:21 by byoshimo         ###   ########.fr       */
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

void	kill_child_processes(t_data *data)
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

void	start_processes(t_philo *philo)
{
	int		i;
	int		exit_status;

	philo->data->forks = sem_open("Forks", O_CREAT, 0777, philo->data->num_philo);
	philo->data->print_sem = sem_open("Print", O_CREAT, 0777, 1);
	i = 0;
	while (i < philo->data->num_philo)
	{
		philo->data->pid[i] = fork();
		if (philo->data->pid[i] == 0)
			dinner(&philo[i]);
		i++;
	}
	sem_close(philo->data->forks);
	sem_close(philo->data->print_sem);
	sem_unlink("Forks");
	sem_unlink("Print");
	exit_status = 0;
	i = 0;
	while (i < philo->data->num_philo && exit_status != 1)
	{
		waitpid(philo->data->pid[i], &exit_status, 0);
		exit_status = WEXITSTATUS(exit_status);
		i++;
	}
	if (exit_status == 1)
		kill_child_processes(philo->data);
}

int	main(int argc, char *argv[])
{
	t_data		*data;
	t_philo		*philo;

	check_args(argc);
	get_data(argc, argv, &data);
	init_philos(data, &philo);
	start_processes(philo);
	free(data->pid);
	free(data);
	free(philo);
}