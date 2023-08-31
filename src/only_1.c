/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:18:23 by lsouquie          #+#    #+#             */
/*   Updated: 2023/08/31 17:03:58 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*u_gonna_starve(void *data)
{
	t_philosophers	*philo;

	philo = (t_philosophers *)data;
	printf("%lld %d has taken a fork\n", get_time() - \
		philo->rules->starting_time, philo->index);
	if (smart_sleep(philo->rules->time_to_die, philo) == 1)
		return (0);
	printf("%lld %d died\n", get_time() - philo->rules->starting_time, \
	philo->index);
	return (0);
}

void	one_philo(t_data*data)
{
	t_philosophers	*philo;

	philo = (t_philosophers *)data->philosophers;
	data->rules.starting_time = get_time();
	philo[0].index = 1;
	merge_mutex(0, data);
	pthread_create(&philo[0].thread_id, NULL, &u_gonna_starve, &philo[0]);
	pthread_join(philo[0].thread_id, NULL);
}
