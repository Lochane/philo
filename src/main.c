/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lochane <lochane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:35:56 by lochane           #+#    #+#             */
/*   Updated: 2023/07/28 00:46:49 by lochane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// number_of_philosophers time_to_die time_to_eat
// time_to_sleep
// [number_of_times_each_philosopher_must_eat]

int	main(int ac, char **argv)
{
	t_data	data;
	(void)ac;
	
	init_struct(&data, atoi(argv[1])); // TODO ajouter mon atoi
	birth_of_philos(&data);
}