/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:07:08 by dkremer           #+#    #+#             */
/*   Updated: 2024/08/07 20:41:11 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	sleeping(t_philo *philo)
{
	if (check_death(philo->data))
		return (1);
	pthread_mutex_lock(&philo->data->sleeping_mutex);
	philo->state = SLEEPING;
	pthread_mutex_unlock(&philo->data->sleeping_mutex);
	philo_msg(philo);
	ft_usleep(philo->data->t_sleep, philo->data);
	return (0);
}

int	thinking(t_philo *philo)
{
	long	tt_think;

	if (check_death(philo->data))
		return (1);
	if (philo->data->philo_n % 2)
	{
		tt_think = (philo->data->t_eat * 2) - philo->data->t_sleep;
		if (tt_think < 0)
			tt_think = 0;
		ft_usleep(tt_think, philo->data);
	}
	pthread_mutex_lock(&philo->data->state_mutex);
	philo->state = THINKING;
	pthread_mutex_unlock(&philo->data->state_mutex);
	philo_msg(philo);
	return (0);
}

static int	forking(t_philo *philo)
{
	if (check_death(philo->data))
		return (1);
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
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (1);
	}
	if (check_death(philo->data))
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (1);
	}
	pthread_mutex_lock(&philo->data->state_mutex);
	philo->state = EATING;
	pthread_mutex_unlock(&philo->data->state_mutex);
	pthread_mutex_lock(&philo->data->eating_mutex);
	philo->last_eat = get_current_time();
	philo->meal_c++;
	pthread_mutex_unlock(&philo->data->eating_mutex);
	philo_msg(philo);
	ft_usleep(philo->data->t_eat, philo->data);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (0);
}

void	*philo(void *philo)
{
	t_philo	*philo_data;

	philo_data = (t_philo *)philo;
	if (philo_data->id % 2)
		ft_usleep((philo_data->data->t_die / 2), philo_data->data);
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
