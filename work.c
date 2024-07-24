/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:07:08 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/24 17:52:48 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"
#include "includes/philo_types.h"

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
	philo_msg(philo, philo->id, THINKING);
}

void	sleeping(t_philo *philo)
{
	philo_msg(philo, philo->id, SLEEPING);
	ft_usleep(philo->data->t_sleep, philo->data);
}

static int	forking(t_philo *philo)
{
	philo->state = FORKING;
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(&philo->data->dead);
	if (philo->data->died == true)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(&philo->data->dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->dead);
	philo_msg(philo, philo->id, FORKING);
	philo_msg(philo, philo->id, FORKING);
	return (0);
}

int	eating(t_philo *philo)
{
	if (forking(philo))
		return (1);
	philo->state = EATING;
	philo_msg(philo, philo->id, EATING);
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

void	*philo(void *philo)
{
	t_philo	*philo_data;

	philo_data = philo;
	philo_data->start = get_current_time();
	if (philo_data->data->philo_n == 1)
	{
		pthread_mutex_lock(philo_data->l_fork);
		philo_msg(philo_data, philo_data->id, FORKING);
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
