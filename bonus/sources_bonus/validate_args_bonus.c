/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 20:55:15 by byoshimo          #+#    #+#             */
/*   Updated: 2023/07/14 21:41:33 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	print_error(void)
{
	printf("Wrong arguments!\nUsage:\n./philo number_of_philosophers");
	printf(" time_to_die time_to_eat time_to_sleep ");
	printf("[number_of_times_each_philosopher_must_eat]\n");
	exit(1);
}

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	check_args(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		if (ft_atol(argv[i]) > 2147483647 || ft_atol(argv[i]) < 0)
			print_error();
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				print_error();
			j++;
		}
		i++;
	}
	if (argc < 5 || argc > 6)
		print_error();
}
