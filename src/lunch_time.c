/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lunch_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 11:19:41 by lsouquie          #+#    #+#             */
/*   Updated: 2023/08/09 12:15:01 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void need_to_eat(void *data, int philo)
{
	t_data *hungry_struct;

	hungry_struct = data;
	hungry_struct->philosophers->tic_tac = 0;
	gettimeofday(&hungry_struct->philosophers->time, NULL);
	printf("%ld %d has taken a fork\n",hungry_struct->philosophers->time.tv_usec , \
	hungry_struct->philosophers->index);
	while(hungry_struct->philosophers->tic_tac <= \
	hungry_struct->philosophers->rules.time_to_eat)
		hungry_struct->philosophers->tic_tac++;
	// pick_fork(philo, philo);
	// pick_fork(philo, (philo + 1)%data->nb_philo);
}

void done_eating(t_data *data, int philo)
{
	// put_down_fork(philo, philo);
	// put_down_fork(philo, (philo + 1)%data->nb_philo);
	(void)data;
	(void)philo;
}