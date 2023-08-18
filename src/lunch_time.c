/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lunch_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 11:19:41 by lsouquie          #+#    #+#             */
/*   Updated: 2023/08/18 19:22:01 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"


void lunch_time(void *data)
{
	t_philosophers *hungry_struct;

	hungry_struct = (t_philosophers *)data;
	pthread_mutex_lock(&hungry_struct->fork_left);
	printf("%lld %d has taken a fork\n", get_time() - hungry_struct->rules->starting_time, hungry_struct->index);
	pthread_mutex_lock(hungry_struct->fork_right);
	printf("%lld %d has taken a fork\n", get_time() - hungry_struct->rules->starting_time, hungry_struct->index);
	printf("%lld %d is eating\n", get_time() - hungry_struct->rules->starting_time, hungry_struct->index);
	smart_sleep(hungry_struct->rules->time_to_eat);
	pthread_mutex_unlock(&hungry_struct->fork_left);
	pthread_mutex_unlock(hungry_struct->fork_right);
}