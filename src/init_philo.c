/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:38:46 by lochane           #+#    #+#             */
/*   Updated: 2023/08/11 19:19:24 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_struct(t_data *data, char **argv)
{
	int	i;

	i = 0;
	data->rules.nb_philo = ft_atoi(argv[1]);
	data->rules.time_to_die = ft_atoi(argv[2]);
	data->rules.time_to_eat = ft_atoi(argv[3]);
	data->rules.time_to_sleep = ft_atoi(argv[4]);
	// data->philosophers->rules.starving_time = ft_atoi(argv[5]);
	while (i < data->rules.nb_philo)
	{
		data->philosophers[i].data = data;
		data->philosophers[i].index = 0;	
		data->philosophers[i].tic_tac = 0;		
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
	while(i < data->rules.nb_philo)
	{
		init_philo[i].index = i;
		pthread_create(&init_philo[i].thread_id, NULL, &philo_routine, &init_philo[i]);
		pthread_join(init_philo[i].thread_id, NULL);
		i++;
	}
}

printf("%d\n", get_time() - data->rule.starting_time)