/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:53:52 by dkremer           #+#    #+#             */
/*   Updated: 2024/08/01 16:31:25 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	create_threads(t_philo *philo_data, t_data *data)
{
	int	i;
	int	stop;
	int	threads_created;

	i = -1;
	threads_created = 0;
	while (++i < data->philo_n)
	{
		philo_data = &data->philo[i];
		pthread_mutex_lock(&data->died_mutex);
		stop = data->died;
		pthread_mutex_unlock(&data->died_mutex);
		if (stop)
			break ;
		if (pthread_create(&philo_data->thread, NULL, &philo, philo_data))
		{
			error("THREAD ERROR!\n");
			break ;
		}
		threads_created++;
	}
	return (threads_created);
}
