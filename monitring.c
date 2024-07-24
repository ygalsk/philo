/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitring.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:53:45 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/24 17:39:13 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"
#include "includes/philo_types.h"

int	time_check(t_data *data)
{
	int		i;
	long	now;

	i = 0;
	while (i < data->philo_n)
	{
		pthread_mutex_lock(&data->eat);
		now = get_current_time();
		if (now - data->philo[i].last_eat >= data->t_die \
					&& data->philo[i].state != EATING)
		{
			pthread_mutex_unlock(&data->eat);
			philo_msg(&data->philo[i], data->philo[i].id, DEAD);
			return (1);
		}
		pthread_mutex_unlock(&data->eat);
		i++;
	}
	return (0);
}

int	meal_check(t_data *data)
{
	t_philo	*philo_d;
	int		i;
	int		all_ate;

	i = 0;
	all_ate = 0;
	philo_d = data->philo;
	if (data->m_count == -1)
		return (0);
	while (i < data->philo_n)
	{
		pthread_mutex_lock(&data->eat);
		if (philo_d[i].meal_c >= data->m_count)
			all_ate++;
		pthread_mutex_unlock(&data->eat);
		i++;
	}
	if (all_ate == data->philo_n)
		return (1);
	return (0);
}

void	monitoring(t_data *data)
{
	while (data->died == false)
	{
		if (time_check(data) || meal_check(data))
		{
			pthread_mutex_lock(&data->dead);
			data->died = true;
			pthread_mutex_unlock(&data->dead);
			break ;
		}
	}
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
	monitoring(data);
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
