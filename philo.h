/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:35:42 by lsouquie          #+#    #+#             */
/*   Updated: 2023/08/28 19:17:18 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

typedef unsigned short bool;
# define false 0
# define true 1

# include <pthread.h>
# include <stdio.h>  
# include <stdlib.h>
# include <sys/time.h>
# include "struct.h"
# include <unistd.h>





int		check_integrity(char **argv);
void	birth_of_philos(t_data *data);
void	init_struct(t_data *data, char **argv);
void 	*philo_routine(void *data);
long long int	get_time();


int lunch_time(void *data);
void death_incomming(void *data);


int     ft_atoi(const char *str);
int	smart_print(void *data, char * str);
int    smart_sleep(int time, void *data);

#endif