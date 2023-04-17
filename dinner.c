
#include "philo.h"

static void	philo_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->first_death == 0)
		printf("%ld %d died\n", get_current_time(philo->data), philo->id);
	philo->data->first_death = 1;
	pthread_mutex_unlock(&philo->data->death_mutex);
}

static void	get_forks(t_philo **philo)
{
	if ((*philo)->id % 2 == 1)
	{
		pthread_mutex_lock((*philo)->left_fork);
		print_state(*philo, "has taken a fork");
		pthread_mutex_lock((*philo)->right_fork);
		print_state(*philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock((*philo)->right_fork);
		print_state(*philo, "has taken a fork");
		pthread_mutex_lock((*philo)->left_fork);
		print_state(*philo, "has taken a fork");
	}
}

static void	eat(t_philo **philo)
{
	get_forks(philo);
	print_state(*philo, "is eating");
	if ((*philo)->data->time_to_die < (*philo)->data->time_to_eat) 
	// || (get_current_time((*philo)->data) - (*philo)->time_since_last_meal + (*philo)->data->time_to_eat > (*philo)->data->time_to_die))
	{
		usleep((*philo)->data->time_to_die * 1000);
		philo_died(*philo);
	}
	else
	{
		(*philo)->time_since_last_meal = get_current_time((*philo)->data);
		usleep((*philo)->data->time_to_eat * 1000);
	}
	pthread_mutex_unlock((*philo)->left_fork);
	pthread_mutex_unlock((*philo)->right_fork);
	(*philo)->num_meals++;
}

static void	sleep_time(t_philo *philo)
{
	print_state(philo, "is sleeping");
	if (get_current_time(philo->data) - philo->time_since_last_meal
		+ philo->data->time_to_sleep > philo->data->time_to_die)
	{
		usleep((philo->data->time_to_die - philo->data->time_to_eat) * 1000);
		philo_died(philo);
	}
	else
	{
		usleep(philo->data->time_to_sleep * 1000);
		print_state(philo, "is thinking");
	}
}

void	*dinner(void *philo)
{
	t_philo	*tmp;

	tmp = (t_philo *)philo;
	if (tmp->data->num_philo == 1)
	{
		pthread_mutex_lock(tmp->right_fork);
		print_state(tmp, "has taken a fork");
		usleep(tmp->data->time_to_die * 1000);
		philo_died(tmp);
		pthread_mutex_unlock(tmp->right_fork);
		free(philo);
		return (NULL);
	}
	while ((!check_if_died(philo) && tmp->num_meals < tmp->data->num_times_to_eat)
		|| (!check_if_died(philo) && tmp->data->num_times_to_eat == -1))
	{
		eat(&tmp);
		if (check_if_died(philo))
			break ;
		sleep_time(tmp);
	}
	free(philo);
	return (NULL);
}
