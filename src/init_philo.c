/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:38:46 by lochane           #+#    #+#             */
/*   Updated: 2023/08/23 16:52:34 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	manage_death_mutex(int i, t_data *data)
{
	if (i > 0)
		data->philosophers[i].check_death = data->philosophers[0].check_death;
	else
		data->philosophers[i].check_death = &data->check_death;
	// printf("%p\n", data->philosophers[i].check_death);
}

void	init_struct(t_data *data, char **argv)
{
	int	i;

	i = 0;
	data->rules.nb_philo = ft_atoi(argv[1]);
	data->rules.time_to_die = ft_atoi(argv[2]);
	data->rules.time_to_eat = ft_atoi(argv[3]);
	data->rules.time_to_sleep = ft_atoi(argv[4]);
	data->rules.starting_time = 0;
	// data->philosophers->rules.starving_time = ft_atoi(argv[5]);
	while (i < data->rules.nb_philo)
	{
		data->philosophers[i].rules = &data->rules;
		data->philosophers[i].index = 0;	
		data->philosophers[i].last_meal = 0;	
		i++;
	}
}

int	check_integrity(char **argv)
{
	int i;
	int j;
	
	i = 1;
	j = 0;
	while(argv[i])
	{
		j = 0;
		while(argv[i][j])
		{
			if(argv[i][j] >= '0' && argv[i][j] <= '9')
				j++;
			else
				return (0);
		}
		i++;
	}
	return (1);
}

void	birth_of_philos(t_data *data)
{
	int	i;
	
	i = 0;
	t_philosophers	*init_philo;
	
	init_philo = (t_philosophers *)data->philosophers;
	data->rules.starting_time = get_time();
	pthread_mutex_lock(&init_philo->mutex);
	while(i < data->rules.nb_philo)
	{
		init_philo[i].index = i + 1;
		manage_death_mutex(i, data);
		if (i == data->rules.nb_philo -1)
			init_philo[i].fork_right = &init_philo[0].fork_left;
		else
			init_philo[i].fork_right = &init_philo[i + 1].fork_left;
		pthread_create(&init_philo[i].thread_id, NULL, &philo_routine, &init_philo[i]);
		usleep(10);
		i++;
	}
	pthread_mutex_unlock(&init_philo->mutex);	
	i = 0;	
	while(i < data->rules.nb_philo)
	{
		pthread_join(init_philo[i].thread_id, NULL);
		i++;	
	}


}
