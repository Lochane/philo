/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:38:41 by lochane           #+#    #+#             */
/*   Updated: 2023/08/30 17:04:48 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	death_incomming(void *data)
{
	t_philosophers	*reaper;

	reaper = (t_philosophers *)data;
	if (((get_time() - reaper->rules->starting_time) - reaper->last_meal > \
	reaper->rules->time_to_die))
	{
		pthread_mutex_lock(reaper->mutex);
		reaper->rules->someone_is_dead = TRUE;
		pthread_mutex_unlock(reaper->mutex);
	}
	return ;
}

int	pick_1st_fork(void *data)
{
	t_philosophers	*gluttony;

	gluttony = (t_philosophers *)data;
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

int	pick_2nd_fork(void *data)
{
	t_philosophers	*gluttony;

	gluttony = (t_philosophers *)data;
	if (gluttony->index % 2)
	{
		pthread_mutex_lock(gluttony->fork_right);
		if (smart_print(gluttony, "has taken a fork") == 1)
		{
			pthread_mutex_unlock(&gluttony->fork_left);
			pthread_mutex_unlock(gluttony->fork_right);
			return (1);
		}
	}
	else
	{
		pthread_mutex_lock(&gluttony->fork_left);
		if (smart_print(gluttony, "has taken a fork") == 1)
		{
			pthread_mutex_unlock(gluttony->fork_right);
			pthread_mutex_unlock(&gluttony->fork_left);
			return (1);
		}
	}
	return (0);
}

int	lunch_time(void *data)
{
	t_philosophers	*gluttony;

	gluttony = (t_philosophers *)data;
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
	smart_sleep(gluttony->rules->time_to_eat, gluttony);
	pthread_mutex_unlock(&gluttony->fork_left);
	pthread_mutex_unlock(gluttony->fork_right);
	return (0);
}

int	thinking_time(void *data)
{
	t_philosophers	*think_struct;

	think_struct = data;
	if (smart_print(think_struct, "is thinking") == 1)
		return (1);
	smart_sleep(think_struct->rules->time_to_eat, think_struct);
	return (0);
}
