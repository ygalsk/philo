/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:28:22 by dkremer           #+#    #+#             */
/*   Updated: 2024/08/07 17:31:26 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include "philo_types.h"

// utils
size_t	get_current_time(void);
void	ft_usleep(size_t milliseconds, t_data *data);
int		ft_isdigit(const char *c);
size_t	ft_strlen(const char *s);
int		ft_atoi(const char *str);
int		error(char *msg);
void	free_and_exit(t_data *data);
//init
int		init_thread(t_data *data);
int		init_data(t_data *data, int argc, char **argv);
//philo stuff
void	philo_msg(t_philo *philo);
void	*philo(void *philo);
//checkers
int		meal_check(t_data *data);
int		time_check(t_data *data);
int		checker(t_philo *philo);
int		check_death(t_data *data);
int		set_death(t_data *data, int i);
//threads
int		create_threads(t_philo *philo_data, t_data *data);
int		work(t_data *data);

#endif
