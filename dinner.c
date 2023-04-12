
#include "philo.h"

int	check_if_died(t_philo *philo)
{
	if (philo->data->first_death)
		return (1);
	if (get_current_time(philo->data) - philo->time_since_last_meal < philo->data->time_to_die)
		return (0);
	return (1);
}

static void	eat(t_philo **philo)
{
	if ((*philo)->id % 2 == 1)
	{
		pthread_mutex_lock((*philo)->left_fork);
		if (!check_if_died(*philo))
			print_state(*philo, "has taken a fork");
		pthread_mutex_lock((*philo)->right_fork);
		if (!check_if_died(*philo))
			print_state(*philo, "has taken a fork");
	}
	else if (!check_if_died(*philo))
	{
		pthread_mutex_lock((*philo)->right_fork);
		if (!check_if_died(*philo))
			print_state(*philo, "has taken a fork");
		pthread_mutex_lock((*philo)->left_fork);
		if (!check_if_died(*philo))
			print_state(*philo, "has taken a fork");
	}
	// if (check_if_died(*philo))
	// {
	// 	print_state(*philo, "died");
	// 	//clean and exit
	// }
	if (!check_if_died(*philo))
	{
		print_state(*philo, "is eating");
		if ((*philo)->data->time_to_die < (*philo)->data->time_to_eat)
		//|| (get_current_time((*philo)->data) - (*philo)->time_since_last_meal + (*philo)->data->time_to_eat > (*philo)->data->time_to_die))
		{
			usleep((*philo)->data->time_to_die * 1000);
			print_state(*philo, "died");
			(*philo)->data->first_death = 1;
		}
		else
		{
			(*philo)->time_since_last_meal = get_current_time((*philo)->data);
			usleep((*philo)->data->time_to_eat * 1000);
		}
	}
	pthread_mutex_unlock((*philo)->left_fork);
	pthread_mutex_unlock((*philo)->right_fork);
	(*philo)->num_meals++;
}

void	sleep_time(t_philo *philo)
{
	print_state(philo, "is sleeping");
	if (get_current_time(philo->data) - philo->time_since_last_meal
		+ philo->data->time_to_sleep > philo->data->time_to_die)
	{
		usleep((philo->data->time_to_die - philo->data->time_to_eat) * 1000);
		// if (!check_if_died(philo))
		print_state(philo, "died");
		philo->data->first_death = 1;
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
		usleep(tmp->data->time_to_die * 1000);
		print_state(tmp, "died");
		free(philo);
		return (NULL);
	}
	while ((!check_if_died(philo) && tmp->num_meals < tmp->data->num_times_to_eat)
		|| (!check_if_died(philo) && tmp->data->num_times_to_eat == -1))
	{
		eat(&tmp);
		// if (get_current_time(tmp->data) - tmp->time_since_last_meal < tmp->data->time_to_die)
		// {
		// 	print_state(tmp, "is sleeping");
		// 	usleep(tmp->data->time_to_sleep * 1000);
		// }
		// else
		// {
		// 	printf("%d died\n", tmp->id);
		// 	free(philo);
		// 	return (NULL);
		// }
		// printf("%d\n", tmp->is_dead);
		if (check_if_died(philo))
			break ;
		sleep_time(tmp);
		// if (get_current_time(tmp->data) - tmp->time_since_last_meal < tmp->data->time_to_die)
		// {
		// 	print_state(tmp, "is thinking");
		// }
		// else
		// {
		// 	printf("%d died\n", tmp->id);
		// 	free(philo);
		// 	return (NULL);
		// }
	}
	free(philo);
	return (NULL);
}
