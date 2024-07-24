/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:51:32 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/24 17:08:27 by dkremer          ###   ########.fr       */
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
	if (data->philo_a)
	{
		while (i < data->philo_n)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->philo);
	}
	if (data->fork_a)
		free(data->forks);
	exit(1);
}

void	philo_msg(t_philo *philo, int id, t_state state)
{
	long int	time;

	time = get_current_time() - philo->start;
	pthread_mutex_lock(&philo->data->msg);
	if (state == DEAD)
		printf("%ld %d died\n", time, id);
	else if (state == FORKING)
		printf("%ld %d has taken a fork\n", time, id);
	else if (state == EATING)
		printf("%ld %d is eating\n", time, id);
	else if (state == SLEEPING)
		printf("%ld %d is sleeping\n", time, id);
	else if (state == THINKING)
		printf("%ld %d is thinking\n", time, id);
	pthread_mutex_unlock(&philo->data->msg);
}
