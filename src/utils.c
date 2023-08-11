/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 10:17:01 by lsouquie          #+#    #+#             */
/*   Updated: 2023/08/11 19:13:28 by lsouquie         ###   ########.fr       */
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

void    smart_sleep(int time)
{
        int     start;
        
        start = get_time();
        time = start + time;
        while (time > get_time())
        {
                usleep(10);
        }
        return ;
}