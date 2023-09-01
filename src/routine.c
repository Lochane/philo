/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:38:41 by lochane           #+#    #+#             */
/*   Updated: 2023/09/01 19:03:28 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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

void	*philo_routine(void *data)
{
	t_philosophers	*philo;

	philo = (t_philosophers *)data;
	pthread_mutex_lock(philo->mutex);
	pthread_mutex_unlock(philo->mutex);
	if (philo->index % 2)
		usleep(10000);
	while (1)
	{
		if (philo->nb_of_meal == philo->rules->max_meal)
			break ;
		if (lunch_time(philo) == 1)
			break ;
		if (smart_print(philo, "is sleeping") == 1)
			break ;
		if (smart_sleep(philo->rules->time_to_sleep, philo) == 1)
			break ;
		if (thinking_time(philo) == 1)
			break ;
	}
	return (NULL);
}
