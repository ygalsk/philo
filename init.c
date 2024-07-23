/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:52:21 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/23 21:52:51 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data, int argc, char **argv)
{
	data->philo_n = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	data->died = false;
	if (argc == 6)
		data->m_count = ft_atoi(argv[5]);
	else
		data->m_count = -1;
	return (0);
}

static int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_n)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->eat, NULL))
		return (1);
	if (pthread_mutex_init(&data->msg, NULL))
		return (1);
	if (pthread_mutex_init(&data->dead, NULL))
		return (1);
	return (0);
}

static int	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_n)
	{
		data->philo[i].meal_c = 0;
		data->philo[i].id = i + 1;
		data->philo[i].eating = false;
		data->philo[i].start = get_current_time();
		data->philo[i].last_eat = get_current_time();
		data->philo[i].data = data;
		data->philo[i].r_fork = &data->forks[data->philo[i].id - 1];
		if (data->philo[i].id == data->philo_n)
			data->philo[i].l_fork = &data->forks[0];
		else
			data->philo[i].l_fork = &data->forks[data->philo[i].id];
		i++;
	}
	return (0);
}

int	init_thread(t_data *data)
{
	data->philo = malloc(sizeof(t_philo) * data->philo_n);
	if (!data->philo)
		return (1);
	data->philo_a = true;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_n);
	if (!data->forks)
	{
		free(data->philo);
		return (1);
	}
	data->fork_a = true;
	if (init_mutex(data))
	{
		free(data->philo);
		free(data->forks);
		return (1);
	}
	if (init_philo(data))
	{
		free(data->philo);
		free(data->forks);
		return (1);
	}
	return (0);
}
