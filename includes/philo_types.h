/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_types.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 13:22:44 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/25 01:34:37 by dkremer          ###   ########.fr       */
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
	long int		last_eat;
	long int		start;
	struct s_data	*data;
	t_state			state;
	pthread_t		thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}					t_philo;

typedef struct s_data
{
	int				philo_n;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				m_count;
	int				died;
	int				error;
	int				total_meals;
	t_philo			*philo;
	pthread_mutex_t	*forks;	
	pthread_mutex_t	msg;
	pthread_mutex_t	eat;
	pthread_mutex_t	dead;
}					t_data;

#endif
