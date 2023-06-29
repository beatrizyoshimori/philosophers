/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:48:10 by byoshimo          #+#    #+#             */
/*   Updated: 2023/06/28 21:37:07 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_times_to_eat;
	int				dinner_is_over;
	time_t			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	printf_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	dinner_mutex;
	pthread_mutex_t	num_meals_mutex;
}	t_data;

typedef struct s_philo
{
	t_data			*data;
	int				id;
	int				num_meals;
	time_t			time_since_last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

int		get_meals(t_philo *philo);
void	set_meals(t_philo *philo);
int		get_last_meal(t_philo *philo);
void	set_last_meal(t_philo *philo);

void	*dinner(void *philo);

int		dinner_is_over(t_philo *philo);
void	print_state(t_philo *philo, char *state);
int		ft_atoi(const char *nptr);

long	timestamp(void);
long	timenow(long firststamp);

void	*monitoring(void *ptr);

void	create_thread(t_philo *philo);
void	mutexes_init(t_data *data);
void	destroy_mutexes(t_data *data);

void	init_philos(t_data *data, t_philo **philo);
void	get_data(int argc, char *argv[], t_data **data);

#endif