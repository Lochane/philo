/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lochane <lochane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:35:42 by lsouquie          #+#    #+#             */
/*   Updated: 2023/07/28 00:51:18 by lochane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>  
# include <stdlib.h>

typedef struct s_philosophers
{
	pthread_t	thread_id;
}	t_philosophers;

typedef struct s_data
{
	int nb_philo;
	t_philosophers philosophers[250];
}	t_data;

void	birth_of_philos(t_data *data);
void	init_struct(t_data *data, int count);

void *need_to_eat(void *data);

#endif