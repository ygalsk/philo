/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:28:22 by dkremer           #+#    #+#             */
/*   Updated: 2024/06/03 21:29:05 by dkremer          ###   ########.fr       */
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

typedef struct s_philo
{
	int				id;
	int				meal_c;
	bool			eating;
	long int		last_eat;
	struct s_data	*data;
	pthread_t		*r_fork;
	pthread_t		*l_fork;
}					t_philo;

typedef struct s_data
{
	int				philo_n;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	long int		t_start;
	t_philo			*philo;
	pthread_mutex_t	msg;
	pthread_mutex_t	stop;
	pthread_mutex_t	eat;
	pthread_mutex_t	dead;
}					t_data;

size_t				get_current_time(void);
int					ft_usleep(size_t milliseconds);
int					ft_isdigit(const char *c);
size_t				ft_strlen(const char *s);
int					ft_atoi(const char *str);
int					error(char *msg);

#endif
