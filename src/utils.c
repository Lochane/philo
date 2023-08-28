/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 10:17:01 by lsouquie          #+#    #+#             */
/*   Updated: 2023/08/28 19:48:25 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int     ft_atoi(const char *str)
{
        int     i;
        int     neg;
        int     nb;

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
        while (str[i] >= '0' && str[i] <= '9')
        {
                nb = nb * (10) + (str[i] - 48);
                i++;
        }
        return (nb * neg);
}

int	smart_print(void *data, char * str)
{
	t_philosophers *print_struct;
        bool            tmp;

	print_struct = (t_philosophers *)data;
        pthread_mutex_lock(print_struct->check_death);
        if (print_struct->rules->someoneIsDead == true)
        {
                pthread_mutex_unlock(print_struct->check_death);
                return (1);
        }
        death_incomming(print_struct);
        tmp = print_struct->rules->someoneIsDead;
 //       pthread_mutex_unlock(print_struct->check_death);
	if (tmp == false)
	{
		pthread_mutex_lock(print_struct->mutex);
		printf("%lld %d %s\n", get_time() - print_struct->rules->starting_time, print_struct->index, str);
		pthread_mutex_unlock(print_struct->mutex);
                pthread_mutex_unlock(print_struct->check_death);
		return (0);
	}
        else if(tmp == true)
        {
                pthread_mutex_lock(print_struct->mutex);
		printf("%lld %d died\n", get_time() - print_struct->rules->starting_time, print_struct->index);
		pthread_mutex_unlock(print_struct->mutex);
                pthread_mutex_unlock(print_struct->check_death);
	        return (1);
        }
          return (1);

}

int     smart_sleep(int time, void *data)
{
       long long int     start;
        long long int     tfinal;
        t_philosophers *dodo;

        dodo = (t_philosophers *)data;
        start = get_time();
        tfinal = start + time;
        while (tfinal > get_time())
        {
                if (dodo->rules->someoneIsDead == true)
                        return (1);
                usleep(10);
        }
        return (0);
}
