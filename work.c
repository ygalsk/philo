/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:07:08 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/25 03:10:04 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	thinking(t_philo *philo)
{
	philo->state = THINKING;
	philo_msg(philo, philo->id);
	return (0);
}

int	sleeping(t_philo *philo)
{
	philo->state = SLEEPING;
	philo_msg(philo, philo->id);
	ft_usleep(philo->data->t_sleep, philo->data);
	return (0);
}

static int	forking(t_philo *philo)
{
	philo->state = FORKING;
	pthread_mutex_lock(philo->l_fork);
	if (philo->id % 2 == 0) {
		pthread_mutex_lock(philo->l_fork);
		usleep(100); // To avoid a race condition
		pthread_mutex_lock(philo->r_fork);
	} else {
		pthread_mutex_lock(philo->r_fork);
		usleep(100); // To avoid a race condition
		pthread_mutex_lock(philo->l_fork);
	}
	pthread_mutex_lock(&philo->data->dead);
	if (philo->data->died == 1)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(&philo->data->dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->dead);
	philo_msg(philo, philo->id);
	philo_msg(philo, philo->id);
	return (0);
}

int	eating(t_philo *philo)
{
	if (forking(philo))
		return (1);
	philo->state = EATING;
	philo_msg(philo, philo->id);
	philo->last_eat = get_current_time();
	ft_usleep(philo->data->t_eat, philo->data);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	if (philo->data->m_count != -1)
		philo->meal_c += 1;
	if (philo->meal_c == philo->data->m_count)
	{
		pthread_mutex_lock(&philo->data->eat);
		philo->data->total_meals += 1;
		pthread_mutex_unlock(&philo->data->eat);
	}
	return (0);
}

int	checker(t_philo *philo)
{
	if (time_check(philo->data) || meal_check(philo->data))
	{
		pthread_mutex_lock(&philo->data->dead);
		philo->data->died = 1;
		pthread_mutex_unlock(&philo->data->dead);
	}
	pthread_mutex_lock(&philo->data->dead);
	if (philo->data->died == 1)
	{
		pthread_mutex_unlock(&philo->data->dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->dead);
	pthread_mutex_lock(&philo->data->eat);
	if (philo->data->total_meals == philo->data->philo_n)
	{
		pthread_mutex_unlock(&philo->data->eat);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->eat);
	return (0);
}

void	*philo(void *philo)
{
	t_philo	*philo_data;

	philo_data = philo;
	if (philo_data->id % 2)
		ft_usleep(philo_data->data->t_eat, philo_data->data);
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
