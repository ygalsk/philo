/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:51:32 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/25 02:42:23 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	error(char *msg)
{
	write(2, "Error: ", 7);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	return (1);
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
	exit(1);
}

void	philo_msg(t_philo *philo, int id)
{
	pthread_mutex_lock(&philo->data->msg);
	if (philo->state == DEAD)
		printf("%ld %d died\n", get_current_time() - philo->start, id);
	else if (philo->state == FORKING)
		printf("%ld %d has taken a fork\n", get_current_time() - philo->start, id);
	else if (philo->state == EATING)
		printf("%ld %d is eating\n", get_current_time() - philo->start, id);
	else if (philo->state == SLEEPING)
		printf("%ld %d is sleeping\n", get_current_time() - philo->start, id);
	else if (philo->state == THINKING)
		printf("%ld %d is thinking\n", get_current_time() - philo->start, id);
	pthread_mutex_unlock(&philo->data->msg);
}
