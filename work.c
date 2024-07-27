/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:07:08 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/27 21:51:03 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->state_mutex);
	if (philo->data->died == 1)
	{
		pthread_mutex_unlock(&philo->data->state_mutex);
		return (1);
	}
	philo->state = SLEEPING;
	pthread_mutex_unlock(&philo->data->state_mutex);
	philo_msg(philo);
	ft_usleep(philo->data->t_sleep, philo->data);
	return (0);
}

int	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->state_mutex);
	if (philo->data->died == 1)
	{
		pthread_mutex_unlock(&philo->data->state_mutex);
		return (1);
	}
	philo->state = THINKING;
	pthread_mutex_unlock(&philo->data->state_mutex);
	philo_msg(philo);
	return (0);
}

static int	forking(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->state_mutex);
	if (philo->data->died)
	{
		pthread_mutex_unlock(&philo->data->state_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->state_mutex);
	pthread_mutex_lock(philo->l_fork);
	philo->state = FORKING;
	philo_msg(philo);
	pthread_mutex_lock(philo->r_fork);
	philo_msg(philo);
	return (0);
}

int	eating(t_philo *philo)
{
	if (time_check(philo->data))
		return (1);
	pthread_mutex_lock(&philo->data->state_mutex);
	if (philo->data->died == 1)
	{
		pthread_mutex_unlock(&philo->data->state_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->state_mutex);
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

void	*philo(void *philo)
{
	t_philo	*philo_data;

	philo_data = philo;
	philo_data->start = get_current_time();
	if (philo_data->id % 2)
		ft_usleep(philo_data->data->t_die / 2, philo_data->data);
	while (1)
	{
		if (eating(philo_data) || checker(philo_data))
			break ;
		if (sleeping(philo_data) || checker(philo_data))
			break ;
		if (thinking(philo_data) || checker(philo_data))
			break ;
	}
	return (NULL);
}
