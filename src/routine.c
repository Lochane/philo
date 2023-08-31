/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:38:41 by lochane           #+#    #+#             */
/*   Updated: 2023/08/31 21:10:02 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	death_incomming(t_philosophers *reaper)
{

	if (((get_time() - reaper->rules->starting_time) - reaper->last_meal > \
		reaper->rules->time_to_die))
	{
		pthread_mutex_lock(reaper->check_death);		
		reaper->rules->someone_is_dead += 1;
		if (reaper->rules->someone_is_dead == TRUE)
		{
			printf("%lld %d died\n", get_time() - reaper->rules->starting_time, \
		reaper->index);
		}
		pthread_mutex_unlock(reaper->check_death);
		return (1);
	}
	return (0);
}

int	pick_1st_fork(t_philosophers *gluttony)
{
	if (gluttony->index % 2)
	{
		pthread_mutex_lock(&gluttony->fork_left);
		if (smart_print(gluttony, "has taken a fork") == 1)
		{
			pthread_mutex_unlock(&gluttony->fork_left);
			return (1);
		}
	}
	else
	{
		pthread_mutex_lock(gluttony->fork_right);
		if (smart_print(gluttony, "has taken a fork") == 1)
		{
			pthread_mutex_unlock(gluttony->fork_right);
			return (1);
		}
	}
	return (0);
}

int	pick_2nd_fork(t_philosophers *gluttony)
{
	if (gluttony->index % 2)
		pthread_mutex_lock(gluttony->fork_right);
	else
		pthread_mutex_lock(&gluttony->fork_left);
	if (smart_print(gluttony, "has taken a fork") == 1)
	{
		pthread_mutex_unlock(gluttony->fork_right);
		pthread_mutex_unlock(&gluttony->fork_left);
		return (1);
	}
	return (0);
}

int	lunch_time(t_philosophers *gluttony)
{
	if (pick_1st_fork(gluttony) == 1)
		return (1);
	if (pick_2nd_fork(gluttony) == 1)
		return (1);
	if (smart_print(gluttony, "is eating") == 1)
	{
		pthread_mutex_unlock(&gluttony->fork_left);
		pthread_mutex_unlock(gluttony->fork_right);
		return (1);
	}
	gluttony->last_meal = get_time() - gluttony->rules->starting_time;
	gluttony->nb_of_meal += 1;
	if (smart_sleep(gluttony->rules->time_to_eat, gluttony) == 1)
	{
		pthread_mutex_unlock(&gluttony->fork_left);
		pthread_mutex_unlock(gluttony->fork_right);
		return (1);
	}
	pthread_mutex_unlock(&gluttony->fork_left);
	pthread_mutex_unlock(gluttony->fork_right);
	return (0);
}

int	thinking_time(t_philosophers *philo)
{
	if (smart_print(philo, "is thinking") == 1)
		return (1);
	if (philo->rules->nb_philo % 2 != 0)
		if (smart_sleep(philo->rules->time_to_eat - 10, philo) == 1)
			return (1);
	return (0);
}
