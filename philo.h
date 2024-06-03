/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:28:22 by dkremer           #+#    #+#             */
/*   Updated: 2024/06/03 17:01:07 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

size_t	get_current_time(void);
int		ft_usleep(size_t milliseconds);
int		ft_isdigit(const char *c);
size_t	ft_strlen(const char *s);
int		ft_atoi(const char *str);
int		error(char *msg);

#endif
