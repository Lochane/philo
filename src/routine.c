/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:38:41 by lochane           #+#    #+#             */
/*   Updated: 2023/08/18 19:02:40 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long long int	get_time()
{
		struct timeval time;
		long long int	current_time;
		
		gettimeofday(&time, NULL);
		current_time = time.tv_sec * 1000 + time.tv_usec / 1000;
		return (current_time);
}

void thinking_time(void *data)
{
	t_philosophers *think_struct;

	think_struct = data;
	printf("%lld %d is thinking\n", get_time() - think_struct->rules->starting_time, think_struct->index);
}

void *philo_routine(void *data)
{
	t_philosophers *philo;

	philo = (t_philosophers *)data;
	while (1)
	{
		pthread_mutex_lock(&philo->mutex);
		lunch_time(philo);
		pthread_mutex_unlock(&philo->mutex);
		pthread_mutex_lock(&philo->mutex);
		printf("%lld %d is sleeping\n", get_time() - philo->rules->starting_time, philo->index);
		smart_sleep(philo->rules->time_to_sleep);
		pthread_mutex_unlock(&philo->mutex);
		if (philo->index % 2 != 0)
		{
			pthread_mutex_lock(&philo->mutex);
			thinking_time(philo);
			pthread_mutex_unlock(&philo->mutex);
		}	
	}
	return NULL;
}