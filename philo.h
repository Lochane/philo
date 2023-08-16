/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:35:42 by lsouquie          #+#    #+#             */
/*   Updated: 2023/08/16 19:34:16 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

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


void need_to_eat(void *data);
void done_eating(t_data *data, int philo);


int     ft_atoi(const char *str);
int     ft_isdigit(int c);

#endif