/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:35:56 by lochane           #+#    #+#             */
/*   Updated: 2023/08/16 19:35:32 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// number_of_philosophers time_to_die time_to_eat
// time_to_sleep
// [number_of_times_each_philosopher_must_eat]

void	manage_mutex(t_data *data, int allow)
{
	int i;

	i = 0;
	while (i <= data->rules.nb_philo)
	{
		if (allow == 0)
		{
			pthread_mutex_init(&data->philosophers[i].fork_left, NULL);
			pthread_mutex_init(&data->philosophers[i].mutex, NULL);
		}
		if (allow == 1)
		{
			pthread_mutex_destroy(&data->philosophers[i].fork_left);
			pthread_mutex_destroy(&data->philosophers[i].mutex);
		}
		
	}
}

int	main(int ac, char **argv)
{
	t_data	data;
	
	if (ac != 5)
		return (printf("Error:\nThis program take 5 arguments\n"));
	if (!check_integrity(argv))
		return (printf("Error:\nThis program only take digits\n"));
	manage_mutex(&data, 0);
	init_struct(&data, argv);
	birth_of_philos(&data);
	manage_mutex(&data, 1);
}