/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:35:56 by lochane           #+#    #+#             */
/*   Updated: 2023/08/28 18:18:57 by lsouquie         ###   ########.fr       */
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
	if (allow == 0)
	{
		while (i <= data->rules.nb_philo)
		{
			pthread_mutex_init(&data->philosophers[i].fork_left, NULL);
			i++;
		}
		pthread_mutex_init(&data->check_death, NULL);
		pthread_mutex_init(&data->mutex, NULL);
		pthread_mutex_init(&data->lock, NULL);
	}
	if (allow == 1)
	{
		while (i <= data->rules.nb_philo)
		{
			pthread_mutex_destroy(&data->philosophers[i].fork_left);		
			i++;
		}
		// pthread_mutex_destroy(&data->check_death);
		pthread_mutex_destroy(&data->mutex);
	}
}

int	main(int ac, char **argv)
{
	t_data	data;
	

	// data = malloc(sizeof(t_data));
	if (ac != 5)
		return (printf("Error:\nThis program take 5 arguments\n"));
	if (!check_integrity(argv))
		return (printf("Error:\nThis program only take digits\n"));
	init_struct(&data, argv);
	manage_mutex(&data, 0);
	birth_of_philos(&data);
	manage_mutex(&data, 1);
}