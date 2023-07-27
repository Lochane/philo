/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lochane <lochane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:38:46 by lochane           #+#    #+#             */
/*   Updated: 2023/07/28 00:52:02 by lochane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_struct(t_data *data, int count)
{
	data->nb_philo = count;
}

void	birth_of_philos(t_data *data)
{
	int	i;
	
	i = 0;
	while(i < data->nb_philo)
	{
		pthread_create(&data->philosophers->thread_id, NULL, need_to_eat, NULL);
		i++;
	}
}