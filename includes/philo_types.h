/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_types.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 13:22:44 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/28 00:05:23 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TYPES_H
# define PHILO_TYPES_H

# include "philo.h"

typedef enum e_state
{
	THINKING,
	EATING,
	SLEEPING,
	DEAD,
	FORKING,
}	t_state;

typedef struct s_philo
{
	int				id;
	int				meal_c;
	int				meal_complete;
	t_state			state;
	long int		start;
	long int		last_eat;
	struct s_data	*data;
	pthread_t		thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}					t_philo;

typedef struct s_data
{
	int				philo_n;
	long int		t_die;
	long int		t_eat;
	long int		t_sleep;
	int				m_count;
	int				died;
	int				error;
	int				total_meals;
	t_philo			*philo;
	pthread_mutex_t	*forks;	
	pthread_mutex_t	msg;
	pthread_mutex_t	state_mutex;
	pthread_mutex_t	died_mutex;
}					t_data;

#endif
