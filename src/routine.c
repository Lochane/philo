/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:38:41 by lochane           #+#    #+#             */
/*   Updated: 2023/08/11 19:08:58 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	get_time()
{
		struct timeval time;
		int				current_time;
		
		gettimeofday(&time, NULL);
		current_time = time.tv_sec * 1000 + time.tv_usec / 1000;
		return (current_time);
}

void thinking_time(void *data)
{
	t_data *think_struct;

	think_struct = data;
	think_struct->philosophers->tic_tac = 0;
	printf("%d %d is thinking\n", get_time(), think_struct->philosophers->index);
	while(think_struct->philosophers->tic_tac <= \
	think_struct->rules.time_to_die)
		think_struct->philosophers->tic_tac++;
	printf("starving time\n");
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