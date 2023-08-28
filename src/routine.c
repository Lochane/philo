/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:38:41 by lochane           #+#    #+#             */
/*   Updated: 2023/08/28 19:36:41 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void death_incomming(void *data)
{
	t_philosophers *reaper;
	
	reaper = (t_philosophers *)data;
	if (((get_time() - reaper->rules->starting_time) - reaper->last_meal > reaper->rules->time_to_die))
	{
		pthread_mutex_lock(reaper->mutex);
		reaper->rules->someoneIsDead = true;
  		pthread_mutex_unlock(reaper->mutex);
	}
	return ;
}

long long int	get_time()
{
		struct timeval time;
		long long int	current_time;
		
		gettimeofday(&time, NULL);
		current_time = time.tv_sec * 1000 + time.tv_usec / 1000;
		return (current_time);
}

int lunch_time(void *data)
{
	t_philosophers *gluttony;

	gluttony = (t_philosophers *)data;
	if (gluttony->index % 2)
		pthread_mutex_lock(&gluttony->fork_left);
	else
		pthread_mutex_lock(gluttony->fork_right);
	if (smart_print(gluttony, "has taken a fork") == 1)
		return (1);
	if (gluttony->index % 2)
		pthread_mutex_lock(gluttony->fork_right);
	else
		pthread_mutex_lock(&gluttony->fork_left);
	if (smart_print(gluttony, "has taken a fork") == 1)
		return (1);
	if (smart_print(gluttony, "is eating") == 1)
		return (1);
	gluttony->last_meal = get_time() - gluttony->rules->starting_time;
	if (smart_sleep(gluttony->rules->time_to_eat, gluttony) == 1)
		return (1);
	pthread_mutex_unlock(&gluttony->fork_left);
	pthread_mutex_unlock(gluttony->fork_right);
	return (0);
}


int thinking_time(void *data)
{
	t_philosophers *think_struct;

	think_struct = data;
	if (smart_print(think_struct, "is thinking") == 1)
		return (1);
	if (smart_sleep(think_struct->rules->time_to_eat, think_struct) == 1)
		return (1);
	return (0);
}

void	*philo_routine(void *data)
{
	t_philosophers *philo;

	philo = (t_philosophers *)data;
	while (1)
	{
		if (lunch_time(philo) == 1)
			return NULL;
		if (smart_print(philo, "is sleeping") == 1)
			return NULL;
		if (smart_sleep(philo->rules->time_to_sleep, philo) == 1)
			return NULL;
		if (philo->rules->nb_philo % 2 != 0)
			if (thinking_time(philo) == 1)
				return NULL;
	}
	return NULL;
}