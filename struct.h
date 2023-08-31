/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 19:19:54 by lsouquie          #+#    #+#             */
/*   Updated: 2023/08/31 17:33:24 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef unsigned short	t_bool;
# define FALSE 0
# define TRUE 1

typedef struct s_rules
{
	int						nb_philo;
	int						time_to_eat;
	int						time_to_die;
	int						time_to_sleep;
	int						max_meal;
	long long				starting_time;
	int						someone_is_dead;
}	t_rules;

typedef struct s_philosophers
{
	int				index;
	int				last_meal;
	int				nb_of_meal;
	pthread_mutex_t	fork_left;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*check_death;
	t_rules			*rules;
	pthread_t		thread_id;
}	t_philosophers;

typedef struct s_data
{	
	t_philosophers	*philosophers;
	pthread_mutex_t	check_death;
	pthread_mutex_t	mutex;
	t_rules			rules;
}	t_data;

#endif