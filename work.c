/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:07:08 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/22 17:25:18 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo *philo)
{
	int	t_think;

	if (philo->data->philo_n % 2)
	{
		t_think = (philo->data->t_eat * 2) - philo->data->t_sleep;
		if (t_think < 0)
			t_think = 0;
		ft_usleep(t_think, philo->data);
	}
	philo_msg("is thinking", philo, philo->id);
}

void	sleeping(t_philo *philo)
{
	philo_msg("is sleeping", philo, philo->id);
	ft_usleep(philo->data->t_sleep, philo->data);
}

int	dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead);
	if (philo->data->died == true)
	{
		pthread_mutex_unlock(&philo->data->dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->dead);
	return (0);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	philo_msg("has taken a fork", philo, philo->id);
	pthread_mutex_lock(philo->r_fork);
	philo_msg("has taken a fork", philo, philo->id);
	philo->eating = true;
	philo_msg("is eating", philo, philo->id);
	pthread_mutex_lock(&philo->data->eat);
	philo->last_eat = get_current_time();
	philo->meal_c += 1;
	pthread_mutex_unlock(&philo->data->eat);
	ft_usleep(philo->data->t_eat, philo->data);
	philo->eating = false;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	*philo(void *philo)
{
	t_philo	*philo_data;

	philo_data = philo;
	philo_data->start = get_current_time();
	if (philo_data->data->philo_n == 1)
	{
		pthread_mutex_lock(philo_data->l_fork);
		philo_msg("has taken fork", philo_data, philo_data->id);
		ft_usleep(philo_data->data->t_die, philo_data->data);
		pthread_mutex_unlock(philo_data->l_fork);
		return (0);
	}
	if (philo_data->id % 2)
		ft_usleep(philo_data->data->t_eat, philo_data->data);
	while (philo_data->data->died == false)
	{
		eating(philo_data);
		sleeping(philo_data);
		thinking(philo_data);
	}
	return (NULL);
}
