/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:28:22 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/22 17:25:35 by dkremer          ###   ########.fr       */
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
	long int		start;
	struct s_data	*data;
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
	long int		t_start;
	t_philo			*philo;
	bool			died;
	bool			fork_a;
	bool			philo_a;
	pthread_mutex_t	*forks;	
	pthread_mutex_t	msg;
	pthread_mutex_t	stop;
	pthread_mutex_t	eat;
	pthread_mutex_t	dead;
}					t_data;

size_t				get_current_time(void);
void				ft_usleep(size_t milliseconds, t_data *data);
int					ft_isdigit(const char *c);
size_t				ft_strlen(const char *s);
int					ft_atoi(const char *str);
int					error(char *msg);
int					init_thread(t_data *data);
int					init_data(t_data *data, int argc, char **argv);
int					work(t_data *data);
void				free_and_exit(t_data *data);
void				philo_msg(char *msg, t_philo *philo, int id);
void				*philo(void *philo);
#endif
