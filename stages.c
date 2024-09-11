/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stages.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 23:19:17 by thuy-ngu          #+#    #+#             */
/*   Updated: 2024/09/11 19:30:34 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_dead_case(int stage, t_philo *philo, size_t timestamp)
{
	philo->dead = true;
	if (stage == DIE_BEF_EAT)
		timestamp = philo->info->die_time + philo->last_meal \
		- (philo->info->start_time);
	if (stage == DIE_BEF_SLEEP)
		timestamp = philo->info->die_time + philo->last_meal \
		- (philo->info->start_time);
	printf("%lu %ld %s\n", timestamp, philo->id, "died");
	return ;
}

void	ft_print(int stage, t_philo *philo)
{
	size_t		timestamp;
	static int	finish;

	pthread_mutex_lock(&(philo->info->print_mutex));
	if (finish == 1)
	{
		philo->dead = true;
		pthread_mutex_unlock(&(philo->info->print_mutex));
		return ;
	}
	timestamp = get_time() - (philo->info->start_time);
	if (stage == GET_RIGHT_FORK || stage == GET_LEFT_FORK)
		printf("%lu %ld %s\n", timestamp, philo->id, "has taken a fork");
	else if (stage == THINK)
		printf("%lu %ld %s\n", timestamp, philo->id, "is thinking");
	else if (stage == SLEEP)
		printf("%lu %ld %s\n", timestamp, philo->id, "is sleeping");
	else if (stage == EAT)
		printf("%lu %ld %s\n", timestamp, philo->id, "is eating");
	else if (stage == DEAD || stage == DIE_BEF_EAT || stage == DIE_BEF_SLEEP)
	{
		finish = 1;
		print_dead_case(stage, philo, timestamp);
	}
	pthread_mutex_unlock(&(philo->info->print_mutex));
}

void	eating(t_philo *philo)
{
	ft_print(EAT, philo);
	if (philo->dead)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	philo->last_meal = get_time();
	ft_usleep(philo->info->eat_time);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	philo->nbr_eat += 1;
	if (philo->nbr_eat == philo->info->limitnbr_eat)
		philo->done = true;
}

void	sleeping(t_philo *philo)
{
	ft_print(SLEEP, philo);
	if (philo->dead)
		return ;
	ft_usleep(philo->info->sleep_time);
}

void	thinking(t_philo *philo)
{
	ft_print(THINK, philo);
	if (philo->dead)
		return ;
}
