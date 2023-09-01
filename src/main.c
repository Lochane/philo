/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:35:56 by lochane           #+#    #+#             */
/*   Updated: 2023/09/01 17:13:03 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_integrity(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		j = 0;
		if (ft_atoi(argv[i]) == (0))
			return (printf("Error:\nPut an int inferior to INT MAX \
and superior to 0\n"), 0);
		while (argv[i][j])
		{
			if (argv[i][j] >= '0' && argv[i][j] <= '9')
				j++;
			else
			{
				return (printf("Error:\nThis program only take digits\n"), 0);
			}
		}
		i++;
	}
	return (1);
}

void	manage_mutex(t_data *data, int allow)
{
	int	i;

	i = 0;
	if (allow == 0)
	{
		while (i < data->rules.nb_philo)
		{
			pthread_mutex_init(&data->philosophers[i].fork_left, NULL);
			i++;
		}
		pthread_mutex_init(&data->check_death, NULL);
		pthread_mutex_init(&data->mutex, NULL);
	}
	if (allow == 1)
	{
		while (i < data->rules.nb_philo)
		{
			pthread_mutex_destroy(&data->philosophers[i].fork_left);
			i++;
		}
		pthread_mutex_destroy(&data->check_death);
		pthread_mutex_destroy(&data->mutex);
	}
}

void	*philo_routine(void *data)
{
	t_philosophers	*philo;

	philo = (t_philosophers *)data;
	pthread_mutex_lock(philo->mutex);
	pthread_mutex_unlock(philo->mutex);
	if (philo->index % 2)
		usleep(10000);
	while (philo->rules->someone_is_dead <= 1)
	{
		if (philo->nb_of_meal == philo->rules->max_meal)
			break ;
		if (lunch_time(philo) == 1)
			break ;
		if (smart_print(philo, "is sleeping") == 1)
			break ;
		if (smart_sleep(philo->rules->time_to_sleep, philo, 0) == 1)
			break ;
		if (thinking_time(philo) == 1)
			break ;
	}
	return (NULL);
}

int	main(int ac, char **argv)
{
	t_data	*data;

	if (ac != 6 && ac != 5)
		return (printf("Error:\nThis program take 4 or 5 arguments\n"));
	if (!check_integrity(argv))
		return (1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	if (init_struct(data, argv) == 0)
	{
		free(data);
		return (0);
	}
	manage_mutex(data, 0);
	if (data->rules.nb_philo == 1)
		one_philo(data);
	else
		birth_of_philos(data);
	manage_mutex(data, 1);
	free(data->philosophers);
	free(data);
	return (0);
}
