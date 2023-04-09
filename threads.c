
#include "philo.h"

void	mutexes_init(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&data->printf_mutex, NULL) != 0)
		printf("Failed to init printf mutex.\n");
	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_mutex_init(&data->forks[i++], NULL) != 0)
			printf("Failed to init fork mutex.\n");
	}
}

void	destroy_mutexes(t_data *data)
{
	int	i;
	
	if (pthread_mutex_destroy(&data->printf_mutex) != 0)
		printf("Failed to destroy printf mutex.\n");
	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_mutex_destroy(&data->forks[i++]) != 0)
			printf("Failed to destroy fork mutex.\n");
	}
}