/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 10:17:01 by lsouquie          #+#    #+#             */
/*   Updated: 2023/09/01 18:54:31 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_atoi(const char *str)
{
	int			i;
	int			neg;
	long int	nb;

	i = 0;
	nb = 0;
	neg = 1;
	while ((str[i] >= '\t' && str[i] <= '\r') || (str[i] == ' '))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		neg *= (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9' && nb <= (2147483649))
	{
		nb = nb * (10) + (str[i] - 48);
		i++;
	}
	nb = nb * neg;
	if (nb > 2147483647 || nb < -2147483647 + 1)
		return (0);
	return (nb);
}

int	ft_print(void *data, char *str, int tmp)
{
	t_philosophers	*philo;

	(void)tmp;
	philo = (t_philosophers *)data;
	pthread_mutex_lock(philo->mutex);
	pthread_mutex_lock(philo->check_death);
	if (philo->rules->someone_is_dead)
	{
		pthread_mutex_unlock(philo->check_death);
		pthread_mutex_unlock(philo->mutex);
		return (1);
	}
	printf("%lld %d %s\n", get_time() - philo->rules->starting_time, \
	philo->index, str);
	pthread_mutex_unlock(philo->check_death);
	pthread_mutex_unlock(philo->mutex);
	return (0);
}

int	smart_print(void *data, char *str)
{
	t_philosophers	*philo;
	int				tmp;

	philo = (t_philosophers *)data;
	if (check_deaths(philo))
		return (1);
	tmp = 0;
	if (ft_print(philo, str, tmp) == 1)
		return (1);
	return (0);
}

int	smart_sleep(int time, void *data)
{
	long long int	tfinal;
	t_philosophers	*dodo;

	dodo = (t_philosophers *)data;
	tfinal = get_time() + time;
	while (tfinal > get_time())
	{
		usleep((tfinal - get_time()) % 500);
		if (check_deaths(dodo))
			return (1);
	}
	return (0);
}

long long int	get_time(void)
{
	struct timeval	time;
	long long int	current_time;

	gettimeofday(&time, NULL);
	current_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (current_time);
}
