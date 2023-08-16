/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lunch_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 11:19:41 by lsouquie          #+#    #+#             */
/*   Updated: 2023/08/16 19:56:00 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"


void need_to_eat(void *data)
{
	t_philosophers *hungry_struct;

	hungry_struct = (t_philosophers *)data;
	pthread_mutex_lock(&hungry_struct->fork_left);
	printf("%lld %d has taken a fork\n", get_time() - hungry_struct->rules->starting_time, hungry_struct->index);
	pthread_mutex_lock(hungry_struct->fork_right);
	printf("%lld %d has taken a fork\n", get_time() - hungry_struct->rules->starting_time, hungry_struct->index);
	// pick_fork(philo, (philo + 1)%data->nb_philo);
}

void done_eating(t_data *data, int philo)
{
	// put_down_fork(philo, philo);
	// put_down_fork(philo, (philo + 1)%data->nb_philo);
	(void)data;
	(void)philo;
}