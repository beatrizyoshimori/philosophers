/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:48:10 by byoshimo          #+#    #+#             */
/*   Updated: 2023/04/06 16:40:28 by byoshimo         ###   ########.fr       */
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
	int				first_death;
	time_t			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	printf_mutex;
}	t_data;

typedef struct s_philo
{
	t_data			*data;
	int				id;
	int				num_meals;
	time_t			time_since_last_meal;
	int				is_dead;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

}	t_philo;

void	create_thread(t_data *data);

void	mutexes_init(t_data *data);
void	destroy_mutexes(t_data *data);

void	*dinner(void *philo);

void	print_state(t_philo *philo, char *state);
time_t	get_current_time(t_data *data);
void	get_philo_info(t_data *data, t_philo **philo, int i);
void	get_data(int argc, char *argv[], t_data **data);
int		ft_atoi(const char *nptr);

void	check_args(int argc);

#endif