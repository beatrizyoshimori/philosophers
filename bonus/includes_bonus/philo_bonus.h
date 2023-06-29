/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:02:58 by byoshimo          #+#    #+#             */
/*   Updated: 2023/06/28 20:03:13 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <unistd.h>
# include <fcntl.h>
# include <semaphore.h>
# include <stdlib.h>

typedef struct s_data
{
	int		num_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		num_times_to_eat;
	int		dinner_is_over;
	time_t	start_time;
	sem_t	*forks;
	// pthread_mutex_t	printf_mutex;
	// pthread_mutex_t	meal_mutex;
	// pthread_mutex_t	dinner_mutex;
	// pthread_mutex_t	num_meals_mutex;
}	t_data;

typedef struct s_philo
{
	t_data			*data;
	int				id;
	int				num_meals;
	time_t			time_since_last_meal;
	pid_t			pid;
	// pthread_mutex_t	*left_fork;
	// pthread_mutex_t	*right_fork;
}	t_philo;

int		get_meals(t_philo *philo);
void	set_meals(t_philo *philo);
int		get_last_meal(t_philo *philo);
void	set_last_meal(t_philo *philo);

void	*dinner(t_philo *philo);

int		dinner_is_over(t_philo *philo);
void	print_state(t_philo *philo, char *state);
int		ft_atoi(const char *nptr);

long	timestamp(void);
long	timenow(long firststamp);

// void	*monitoring(void *ptr);

void	init_philos(t_data *data, t_philo **philo);
void	get_data(int argc, char *argv[], t_data **data);

#endif