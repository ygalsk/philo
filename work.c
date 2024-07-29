/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:07:08 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/29 13:11:37 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->died_mutex);
	if (philo->data->died == 1)
	{
		pthread_mutex_unlock(&philo->data->died_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->died_mutex);
	pthread_mutex_lock(&philo->data->state_mutex);
	philo->state = SLEEPING;
	pthread_mutex_unlock(&philo->data->state_mutex);
	philo_msg(philo);
	ft_usleep(philo->data->t_sleep, philo->data);
	return (0);
}

int	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->died_mutex);
	if (philo->data->died == 1)
	{
		pthread_mutex_unlock(&philo->data->died_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->died_mutex);
	pthread_mutex_lock(&philo->data->state_mutex);
	philo->state = THINKING;
	pthread_mutex_unlock(&philo->data->state_mutex);
	philo_msg(philo);
	return (0);
}

static int	forking(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->died_mutex);
	if (philo->data->died)
	{
		pthread_mutex_unlock(&philo->data->died_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->died_mutex);
	pthread_mutex_lock(&philo->data->state_mutex);
	philo->state = FORKING;
	pthread_mutex_unlock(&philo->data->state_mutex);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		pthread_mutex_lock(philo->l_fork);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		pthread_mutex_lock(philo->r_fork);
	}
	philo_msg(philo);
	philo_msg(philo);
	return (0);
}

int	eating(t_philo *philo)
{
	if (forking(philo))
		return (1);
	pthread_mutex_lock(&philo->data->died_mutex);
	if (philo->data->died == 1)
	{
		pthread_mutex_unlock(&philo->data->died_mutex);
		return (1);
	}
	//if (time_check(philo->data))
	//	return (1);
	pthread_mutex_unlock(&philo->data->died_mutex);
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
	int	stop;

	philo_data = (t_philo *)philo;
	stop = 0;
	//pthread_mutex_lock(&philo_data->data->state_mutex);
	//philo_data->start = get_current_time();
	//pthread_mutex_unlock(&philo_data->data->state_mutex);
	if (philo_data->id % 2)
		ft_usleep(philo_data->data->t_die / 2, philo_data->data);
	while (!stop)
	{
		pthread_mutex_lock(&philo_data->data->died_mutex);
		stop = philo_data->data->died;
		pthread_mutex_unlock(&philo_data->data->died_mutex);
		if (!stop)
		{
			if (eating(philo_data) || checker(philo_data))
				break ;
			if (sleeping(philo_data) || checker(philo_data))
				break ;
			if (thinking(philo_data) || checker(philo_data))
				break ;
		}
	}
	return (NULL);
}
