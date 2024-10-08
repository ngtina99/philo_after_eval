/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_and_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 23:19:34 by thuy-ngu          #+#    #+#             */
/*   Updated: 2024/09/13 16:08:09 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error(int sign)
{
	if (sign == ERR_ARG)
	{
		printf(RED "Please put 5 or 6 arguments\n" EOC);
		exit(1);
	}
	else if (sign == ERR_CHECK)
	{
		printf(RED "Please put valid arguments\n" EOC);
		exit(1);
	}
	else if (sign == ERR_MALLOC)
	{
		printf(RED "Memory allocation error\n" EOC);
		exit(1);
	}
	else if (sign == QUIT)
		exit (1);
}

void	destroy_philo(t_philo *philo, pthread_mutex_t *forks, t_info *info)
{
	int	i;

	i = 0;
	while (i < philo->info->nbr_philo)
	{
		pthread_mutex_destroy(&(forks[i]));
		pthread_mutex_destroy(&(philo[i].nbr_eat_mutex));
		pthread_mutex_destroy(&(philo[i].last_meal_mutex));
		pthread_mutex_destroy(&(philo[i].status_mutex));
		pthread_mutex_destroy(&(philo[i].dead_bool_mutex));
		i++;
	}
	pthread_mutex_destroy(&(info->print_mutex));
	free(philo);
	free(forks);
}
