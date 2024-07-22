/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:31:44 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/22 19:10:27 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!ft_isdigit(argv[i]))
			return (1);
		i++;
	}
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > 200)
		return (1);
	if (ft_atoi(argv[2]) < 60 || ft_atoi(argv[3]) < 60 || ft_atoi(argv[4]) < 60)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 4 || argc > 5)
		return (error("INVALID NUMBER OF ARGUMENTS!\n"));
	if (argc == 5 && ft_atoi(argv[4]) < 1)
		return (0);
	if (!check_args(argc, argv))
		return (error("INVALID TYPE OF ARGUMENTS! USE INT_VALUES!\n"));
	if (init_data(&data, argc, argv))
		return (error("INIT ERROR!\n"));
	if (init_thread(&data))
		return (error("THREAD ERROR!\n"));
	work(&data);
	return (0);
}
