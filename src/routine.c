/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:38:41 by lochane           #+#    #+#             */
/*   Updated: 2023/08/09 12:11:56 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void thinking_time(void *data)
{
	t_data *think_struct;

	think_struct = data;
	think_struct->philosophers->tic_tac = 0;
	gettimeofday(&think_struct->philosophers->time, NULL);
	printf("%ld %d is thinking\n",think_struct->philosophers->time.tv_usec , \
	think_struct->philosophers->index);
	while(think_struct->philosophers->tic_tac <= \
	think_struct->philosophers->rules.starving_time)
		think_struct->philosophers->tic_tac++;
}

void *philo_routine(void *data)
{
	t_data *philo;

	philo = (t_data *)data;
	pthread_mutex_lock(&philo->philosophers->mutex);
	thinking_time(philo);
	pthread_mutex_unlock(&philo->philosophers->mutex);
	return NULL;
}