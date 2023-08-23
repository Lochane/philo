/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:38:41 by lochane           #+#    #+#             */
/*   Updated: 2023/08/23 16:56:41 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void death_incomming(void *data)
{
	t_philosophers *death_struct;
	
	death_struct = (t_philosophers *)data;
	if ((get_time() - death_struct->rules->starting_time) - death_struct->last_meal > death_struct->rules->time_to_die)
	{
		printf("%lld %d died\n", get_time() - death_struct->rules->starting_time, death_struct->index);
		pthread_mutex_lock(death_struct->check_death);	
		exit (0);
	}
	// else
	// {
	// 	pthread_mutex_lock(death_struct->check_death);	
	// 	pthread_mutex_unlock(death_struct->check_death);	
	// }
	
}

long long int	get_time()
{
		struct timeval time;
		long long int	current_time;
		
		gettimeofday(&time, NULL);
		current_time = time.tv_sec * 1000 + time.tv_usec / 1000;
		return (current_time);
}

void lunch_time(void *data)
{
	t_philosophers *hungry_struct;

	hungry_struct = (t_philosophers *)data;
	pthread_mutex_lock(&hungry_struct->fork_left);
	printf("%lld %d has taken a fork\n", get_time() - hungry_struct->rules->starting_time, hungry_struct->index);
	death_incomming(hungry_struct);
	pthread_mutex_lock(hungry_struct->fork_right);
	printf("%lld %d has taken a fork\n", get_time() - hungry_struct->rules->starting_time, hungry_struct->index);
	printf("%lld %d is eating\n", get_time() - hungry_struct->rules->starting_time, hungry_struct->index);
	hungry_struct->last_meal = get_time() - hungry_struct->rules->starting_time;
	smart_sleep(hungry_struct->rules->time_to_eat);
	pthread_mutex_unlock(&hungry_struct->fork_left);
	pthread_mutex_unlock(hungry_struct->fork_right);
}

void thinking_time(void *data)
{
	t_philosophers *think_struct;

	think_struct = data;
	printf("%lld %d is thinking\n", get_time() - think_struct->rules->starting_time, think_struct->index);
	smart_sleep(think_struct->rules->time_to_eat);
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
		if (philo->rules->nb_philo % 2 != 0)
		{
			pthread_mutex_lock(&philo->mutex);
			thinking_time(philo);
			pthread_mutex_unlock(&philo->mutex);
		}	
	}
	return NULL;
}