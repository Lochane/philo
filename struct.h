/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 19:19:54 by lsouquie          #+#    #+#             */
/*   Updated: 2023/08/23 16:39:08 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include "philo.h"

typedef struct s_rules
{
	int nb_philo;
	int time_to_eat;
	int time_to_die;
	int time_to_sleep;
	long long	starting_time;
	// int starving_time;	
}	t_rules;

typedef struct s_philosophers
{
	pthread_t	thread_id;
	unsigned int	index;
	pthread_mutex_t fork_left;
	pthread_mutex_t *fork_right;
	pthread_mutex_t mutex;
	pthread_mutex_t *check_death;
	t_rules			*rules;
	int last_meal;
}	t_philosophers;

typedef struct s_data
{	
	t_philosophers philosophers[250];
	pthread_mutex_t check_death;
	t_rules	rules;
}	t_data;

#endif