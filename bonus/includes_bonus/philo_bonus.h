/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:02:58 by byoshimo          #+#    #+#             */
/*   Updated: 2023/07/04 21:52:24 by byoshimo         ###   ########.fr       */
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
# include <signal.h>

typedef struct s_data
{
	int		num_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		num_times_to_eat;
	int		dinner_is_over;
	pid_t	*pid;
	time_t	start_time;
	sem_t	*forks;
	sem_t	*print_sem;
}	t_data;

typedef struct s_philo
{
	t_data			*data;
	int				id;
	int				num_meals;
	time_t			time_since_last_meal;
}	t_philo;

void	*dinner(t_philo *philo);

void	free_all(t_philo *philo);
void	print_state(t_philo *philo, char *state);
int		ft_atoi(const char *nptr);

long	timestamp(void);
long	timenow(long firststamp);

void	init_philos(t_data *data, t_philo **philo);
void	get_data(int argc, char *argv[], t_data **data);

#endif