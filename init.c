/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-mes <hben-mes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:00:25 by hben-mes          #+#    #+#             */
/*   Updated: 2023/05/26 15:50:28 by hben-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philos_connect(t_info *info, t_philos *philosopher)
{
	int	i;

	i = 0;
	while (i < info->philos_num)
	{
		philosopher[i].info = info;
		philosopher[i].philo_id = i + 1;
		if (i == info->philos_num - 1)
			philosopher[i].second_fork = &philosopher[0].fork;
		else
			philosopher[i].second_fork = &philosopher[i + 1].fork;
		i++;
	}
}

long	time_calcul(void)
{
	struct timeval	time_calcul;

	gettimeofday(&time_calcul, NULL);
	return ((time_calcul.tv_sec * 1000) + (time_calcul.tv_usec / 1000));
}

void	philos_routine(t_philos *philosopher)
{
	display("is thinking", philosopher->philo_id, philosopher->info);
	pthread_mutex_lock(&philosopher->fork);
	display("has taken a fork", philosopher->philo_id, philosopher->info);
	pthread_mutex_lock(philosopher->second_fork);
	display("has taken a fork", philosopher->philo_id, philosopher->info);
	philosopher->has_to_die = time_calcul() + philosopher->info->die_chrono;
	display("is eating", philosopher->philo_id, philosopher->info);
	usleep(philosopher->info->eat_chrono * 1000);
	pthread_mutex_unlock(&philosopher->fork);
	pthread_mutex_unlock(philosopher->second_fork);
	display("is sleeping", philosopher->philo_id, philosopher->info);
	usleep(philosopher->info->sleep_chrono * 1000);
}

void	*philos_repeat(void *str)
{
	t_philos	*philosopher;
	int			count;

	count = 0;
	philosopher = (t_philos *)str;
	philosopher->has_to_die = philosopher->info->start_chrono
		+ philosopher->info->die_chrono;
	while (philosopher->info->gotta_eat == 0
		|| count < philosopher->info->gotta_eat)
	{
		philos_routine(philosopher);
		count++;
		usleep(100);
	}
	philosopher->out = 1;
	return (NULL);
}
