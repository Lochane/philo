/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:35:42 by lsouquie          #+#    #+#             */
/*   Updated: 2023/08/09 12:07:31 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>  
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_rules
{
	int nb_philo;
	int time_to_eat;
	int time_to_die;
	int time_to_sleep;
	int starving_time;	
}	t_rules;

typedef struct s_philosophers
{
	pthread_t	thread_id;
	unsigned int	index;
	pthread_mutex_t mutex;
	t_rules			rules;
	int tic_tac;
	struct timeval time;
	
}	t_philosophers;

typedef struct s_data
{	
	t_philosophers philosophers[250];
}	t_data;

int		check_integrity(char **argv);
void	birth_of_philos(t_philosophers *data);
void	init_struct(t_data *data, char **argv);
void 	*philo_routine(void *data);

void need_to_eat(void *data, int philo);
void done_eating(t_data *data, int philo);


int     ft_atoi(const char *str);
int     ft_isdigit(int c);

#endif