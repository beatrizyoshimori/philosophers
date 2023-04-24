#include "philo.h"

long	timestamp(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long	timenow(long firststamp)
{
	return (timestamp() - firststamp);
}

void	msleep(int time_in_ms)
{
	long	start_time;

	start_time = timestamp();
	while ((timestamp() - start_time) < (long)time_in_ms)
		usleep(10);
}

// void	msleep(int time, t_data *data)
// {
// 	long	start_time;

// 	start_time = get_current_time(data);
// 	while ((get_current_time(data) - start_time) < (long)time)
// 		usleep(10);
// }

// time_t	get_current_time(t_data *data)
// {
// 	struct timeval	current_time;
// 	time_t			time_ms;

// 	gettimeofday(&current_time, NULL);
// 	time_ms = (current_time.tv_sec * 1000 + current_time.tv_usec / 1000)
// 		- data->start_time;
// 	return (time_ms);
// }