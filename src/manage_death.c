/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_death.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 18:53:12 by lsouquie          #+#    #+#             */
/*   Updated: 2023/09/01 18:54:45 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_deaths(t_philosophers *philo)
{
	pthread_mutex_lock(philo->check_death);
	if (philo->rules->someone_is_dead == TRUE)
	{
		pthread_mutex_unlock(philo->check_death);
		return (1);
	}
	pthread_mutex_unlock(philo->check_death);
	if (death_incomming(philo))
		return (1);
	return (0);
}

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
