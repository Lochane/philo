/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:38:46 by lochane           #+#    #+#             */
/*   Updated: 2023/08/30 20:11:28 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	merge_mutex(int i, t_data *data)
{
	if (i > 0)
	{
		data->philosophers[i].mutex = data->philosophers[0].mutex;
		data->philosophers[i].check_death = data->philosophers[0].check_death;
	}
	else
	{
		data->philosophers[i].mutex = &data->mutex;
		data->philosophers[i].check_death = &data->check_death;
	}
}

void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->rules.nb_philo)
	{
		data->philosophers[i].rules = &data->rules;
		data->philosophers[i].nb_of_meal = 0;
		data->philosophers[i].index = 0;
		data->philosophers[i].last_meal = 0;
		i++;
	}
}

int	init_struct(t_data *data, char **argv)
{
	int	i;

	i = 0;
	data->rules.nb_philo = ft_atoi(argv[1]);
	data->rules.time_to_die = ft_atoi(argv[2]);
	data->rules.time_to_eat = ft_atoi(argv[3]);
	data->rules.time_to_sleep = ft_atoi(argv[4]);
	data->rules.starting_time = 0;
	data->rules.someone_is_dead = FALSE;
	data->philosophers = malloc(sizeof(t_philosophers) * data->rules.nb_philo);
	if (!data->philosophers)
	{
		free(data);
		return (0);
	}
	if (argv[5])
		data->rules.max_meal = ft_atoi(argv[5]);
	else
		data->rules.max_meal = -1;
	init_philo(data);
	return (1);
}

void	join_philo(t_philosophers *data)
{
	int				i;
	t_philosophers	*init_philo;

	i = 0;
	init_philo = data;
	while (i < init_philo->rules->nb_philo)
	{
		pthread_join(init_philo[i].thread_id, NULL);
		i++;
	}
}

void	birth_of_philos(t_data *data)
{
	int				i;
	t_philosophers	*init_philo;

	i = 0;
	init_philo = (t_philosophers *)data->philosophers;
	pthread_mutex_lock(&data->mutex);
	while (i < data->rules.nb_philo)
	{
		init_philo[i].index = i + 1;
		merge_mutex(i, data);
		if (i == data->rules.nb_philo -1)
			init_philo[i].fork_right = &init_philo[0].fork_left;
		else
			init_philo[i].fork_right = &init_philo[i + 1].fork_left;
		pthread_create(&init_philo[i].thread_id, NULL, &philo_routine, \
				&init_philo[i]);
		i++;
	}
	data->rules.starting_time = get_time();
	pthread_mutex_unlock(&data->mutex);
	join_philo(init_philo);
}
