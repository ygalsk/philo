/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitring.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:53:45 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/25 02:59:42 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"
#include <pthread.h>

int	time_check(t_data *data)
{
	int		i;
	long	now;

	i = 0;
	while (i < data->philo_n)
	{
		pthread_mutex_lock(&data->dead);
		pthread_mutex_lock(&data->eat);
		now = get_current_time();
		if (now - data->philo[i].last_eat >= data->t_die \
					&& data->philo[i].state != EATING)
		{
			data->died = 1;
			data->philo->state = DEAD;
			philo_msg(data->philo, data->philo->id);
			pthread_mutex_unlock(&data->dead);
			pthread_mutex_unlock(&data->eat);
			return (1);
		}
		pthread_mutex_unlock(&data->dead);
		pthread_mutex_unlock(&data->eat);
		i++;
	}
	return (0);
}

int	meal_check(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_n && data->died != 1)
	{
		pthread_mutex_lock(&data->eat);
		if (data->philo[i].meal_c < data->m_count)
		{
			pthread_mutex_unlock(&data->eat);
			break ;
		}
		pthread_mutex_unlock(&data->eat);
		i++;
	}
	if (i == data->philo_n)
		return (1);
	return (0);
}

int	work(t_data *data)
{
	int		i;
	t_philo	*philo_data;

	i = 0;
	while (i < data->philo_n)
	{
		philo_data = &data->philo[i];
		if (pthread_create(&philo_data->thread, NULL, &philo, philo_data))
			return (free_and_exit(data), error("THREAD ERROR2!\n"));
		i++;
	}
	i = 0;
	while (i < data->philo_n)
	{
		philo_data = &data->philo[i];
		if (pthread_join(philo_data->thread, NULL))
			return (free_and_exit(data), error("THREAD ERROR3!\n"));
		i++;
	}
	free_and_exit(data);
	return (0);
}
