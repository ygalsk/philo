/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitring.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:53:45 by dkremer           #+#    #+#             */
/*   Updated: 2024/08/01 16:31:54 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	time_check(t_data *data)
{
	int		i;

	i = -1;
	if (check_death(data))
		return (1);
	while (++i < data->philo_n)
	{
		if (set_death(data, i))
			return (1);
	}
	return (0);
}

int	meal_check(t_data *data)
{
	int	i;

	i = 0;
	if (data->m_count == -1)
		return (0);
	while (i < data->philo_n)
	{
		pthread_mutex_lock(&data->state_mutex);
		if (data->philo[i].meal_c >= data->m_count && \
				!data->philo[i].meal_complete)
		{
			data->total_meals++;
			data->philo[i].meal_complete = 1;
		}
		pthread_mutex_unlock(&data->state_mutex);
		i++;
	}
	pthread_mutex_lock(&data->state_mutex);
	if (data->total_meals == data->philo_n)
	{
		pthread_mutex_unlock(&data->state_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->state_mutex);
	return (0);
}

int	checker(t_philo *philo)
{
	if (time_check(philo->data))
		return (1);
	if (meal_check(philo->data))
		return (1);
	if (check_death(philo->data))
		return (1);
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		stop;

	data = (t_data *)arg;
	stop = 0;
	while (!stop)
	{
		if (time_check(data) || meal_check(data) || check_death(data))
			stop = 1;
		usleep(1000);
	}
	return (NULL);
}

int	work(t_data *data)
{
	int			i;
	t_philo		*philo_data;
	pthread_t	monitor_thread;
	int			threads_created;

	i = -1;
	threads_created = 0;
	philo_data = data->philo;
	if (pthread_create(&monitor_thread, NULL, &monitor_routine, data))
		return (error("MONITOR THREAD ERROR!\n"));
	threads_created = create_threads(philo_data, data);
	while (++i < threads_created)
	{
		philo_data = &data->philo[i];
		if (pthread_join(philo_data->thread, NULL))
			return (error("THREAD JOIN ERROR!\n"));
	}
	if (pthread_join(monitor_thread, NULL))
		return (error("MONITOR THREAD JOIN ERROR!\n"));
	free_and_exit(data);
	return (0);
}
