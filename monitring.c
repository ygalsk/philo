/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitring.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:53:45 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/26 17:53:39 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int time_check(t_data *data)
{
	int i;
	long now;

	i = 0;
	while (i < data->philo_n)
	{
		pthread_mutex_lock(&data->state_mutex);
		now = get_current_time();
		if (now - data->philo[i].last_eat >= data->t_die && data->philo[i].state != EATING)
		{
			data->died = 1;
			pthread_mutex_unlock(&data->state_mutex);
			return (1);
		}
		pthread_mutex_unlock(&data->state_mutex);
		i++;
	}
	return (0);
}

int meal_check(t_data *data)
{
    int i;
    int all_ate;

    i = 0;
    all_ate = 1;
    while (i < data->philo_n)
    {
        pthread_mutex_lock(&data->state_mutex);
        if (data->philo[i].meal_c >= data->m_count && !data->philo[i].meal_complete)
        {
            data->total_meals++;
            data->philo[i].meal_complete = 1;
        }
        pthread_mutex_unlock(&data->state_mutex);
        i++;
    }
    return (all_ate && data->total_meals == data->philo_n);
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
