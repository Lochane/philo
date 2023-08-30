/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:35:42 by lsouquie          #+#    #+#             */
/*   Updated: 2023/08/30 18:50:24 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>  
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include "struct.h"

int				check_integrity(char **argv);
void			birth_of_philos(t_data *data);
int				init_struct(t_data *data, char **argv);
void			*philo_routine(void *data);
long long int	get_time(void);

int				thinking_time(t_philosophers *philo);
int				lunch_time(t_philosophers *gluttony);
void			death_incomming(t_philosophers *reaper);

void			one_philo(t_data*data);

int				ft_atoi(const char *str);
int				smart_print(void *data, char *str);
int				smart_sleep(int time, void *data);

#endif