/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:07:08 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/26 18:41:45 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int sleeping(t_philo *philo)
{
	philo->state = SLEEPING;
	philo_msg(philo);
	ft_usleep(philo->data->t_sleep, philo->data);
	return (0);
}

int thinking(t_philo *philo)
{
	philo->state = THINKING;
	philo_msg(philo);
	return (0);
}

static int forking(t_philo *philo)
{
	philo->state = FORKING;
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(philo->r_fork);
	if (philo->data->died == 1)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (1);
	}
	philo_msg(philo);
	philo_msg(philo);
	return (0);
}

int eating(t_philo *philo)
{
	if (forking(philo))
		return (1);
	pthread_mutex_lock(&philo->data->state_mutex);
	philo->state = EATING;
	philo->last_eat = get_current_time();
	philo->meal_c++;
	pthread_mutex_unlock(&philo->data->state_mutex);
	philo_msg(philo);
	ft_usleep(philo->data->t_eat, philo->data);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (0);
}

int	checker(t_philo *philo)
{
	if (time_check(philo->data) || philo->state == DEAD || philo->data->died == 1)
	{
		pthread_mutex_lock(&philo->data->state_mutex);
		philo->state = DEAD;
		pthread_mutex_unlock(&philo->data->state_mutex);
		philo_msg(philo);
		return (1);
	}
	if (meal_check(philo->data))
		return (1);
	return (0);
}

void *philo(void *philo)
{
	t_philo *philo_data;
	
	philo_data = philo;
	if (philo_data->id % 2)
		ft_usleep(philo_data->data->t_eat, philo_data->data);
	while (1)
	{
		if (eating(philo_data) || checker(philo_data))
			break;
		if (sleeping(philo_data))
			break;
		if (thinking(philo_data))
			break;
	}
	return (NULL);
}
