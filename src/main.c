/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:35:56 by lochane           #+#    #+#             */
/*   Updated: 2023/08/09 10:32:19 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// number_of_philosophers time_to_die time_to_eat
// time_to_sleep
// [number_of_times_each_philosopher_must_eat]

int	main(int ac, char **argv)
{
	t_data	data;
	if (ac != 6)
		return (printf("Error:\nThis program take 5 arguments\n"));
	if (!check_integrity(argv))
		return (printf("Error:\nThis program only take digits\n"));
	pthread_mutex_init(&data.philosophers->mutex, NULL);
	init_struct(&data, argv);
	birth_of_philos(&data);
	pthread_mutex_destroy(&data.philosophers->mutex);
}