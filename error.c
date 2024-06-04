/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:51:32 by dkremer           #+#    #+#             */
/*   Updated: 2024/06/04 17:41:18 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>

int	error(char *msg)
{
	write(2, "Error: ", 7);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	return (1);
}

void free_and_exit(t_data *data)
{
    int i;

    i = 0;
    if (data->philo_a)  // add this check
    {
        while (i < data->philo_n)
        {
            pthread_mutex_destroy(&data->forks[i]);
            i++;
        }
        free(data->philo);
    }
    if (data->fork_a)  // add this check
    {
        free(data->forks);
    }
    exit(1);
}

void	philo_msg(char *msg, t_philo *philo, int id)
{
	if (philo->data->died == false)
	{
		pthread_mutex_lock(&philo->data->msg);
		printf("%ld %d %s\n", get_current_time() - philo->t_start, id, msg);
		pthread_mutex_unlock(&philo->data->msg);
	}
}
