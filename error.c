/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:51:32 by dkremer           #+#    #+#             */
/*   Updated: 2024/08/07 20:16:31 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

// write(2, "\n", 1);
int	error(char *msg)
{
	write(2, "Error: ", 7);
	write(2, msg, ft_strlen(msg));
	return (1);
}

int	set_death(t_data *data, int i)
{
	long	now;

	pthread_mutex_lock(&data->state_mutex);
	pthread_mutex_lock(&data->eating_mutex);
	now = get_current_time();
	if (now - data->philo[i].last_eat >= data->t_die \
		&& data->philo[i].state != EATING)
	{
		pthread_mutex_lock(&data->died_mutex);
		data->died = 1;
		pthread_mutex_unlock(&data->died_mutex);
		data->philo[i].state = DEAD;
		pthread_mutex_unlock(&data->eating_mutex);
		pthread_mutex_unlock(&data->state_mutex);
		pthread_mutex_lock(&data->msg);
		printf("%ld %d died\n", get_current_time() - data->philo[i].start, \
			data->philo[i].id);
		pthread_mutex_unlock(&data->msg);
		return (1);
	}
	pthread_mutex_unlock(&data->eating_mutex);
	pthread_mutex_unlock(&data->state_mutex);
	return (0);
}

int	check_death(t_data *data)
{
	pthread_mutex_lock(&data->died_mutex);
	if (data->died)
	{
		pthread_mutex_unlock(&data->died_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->died_mutex);
	return (0);
}

void	free_and_exit(t_data *data)
{
	int	i;

	i = 0;
	if (data->philo)
	{
		while (i < data->philo_n)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->philo);
		data->philo = NULL;
	}
	if (data->forks)
	{
		free(data->forks);
		data->forks = NULL;
	}
	pthread_mutex_destroy(&data->state_mutex);
	pthread_mutex_destroy(&data->eating_mutex);
	pthread_mutex_destroy(&data->msg);
	pthread_mutex_destroy(&data->died_mutex);
	pthread_mutex_destroy(&data->sleeping_mutex);
	return ;
}

void	philo_msg(t_philo *philo)
{
	if (check_death(philo->data))
		return ;
	pthread_mutex_lock(&philo->data->msg);
	pthread_mutex_lock(&philo->data->state_mutex);
	if (philo->state == FORKING)
		printf("%ld %d has taken a fork\n", get_current_time() - philo->start, \
						philo->id);
	else if (philo->state == EATING)
		printf("%ld %d is eating\n", get_current_time() - philo->start, \
						philo->id);
	else if (philo->state == SLEEPING)
		printf("%ld %d is sleeping\n", get_current_time() - philo->start, \
						philo->id);
	else if (philo->state == THINKING)
		printf("%ld %d is thinking\n", get_current_time() - philo->start, \
						philo->id);
	pthread_mutex_unlock(&philo->data->msg);
	pthread_mutex_unlock(&philo->data->state_mutex);
}
