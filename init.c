/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-mes <hben-mes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:00:25 by hben-mes          #+#    #+#             */
/*   Updated: 2023/05/06 16:00:25 by hben-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void	philos_connect(t_info *info, t_philos *philo)
{
	int	i;

	i = 0;
	while (i < info->philos_num)
	{
		philo[i].info = info;
		philo[i].philo_id = i + 1;
		if (i == info->philos_num - 1)
			philo[i].second_fork = &philo[0].fork;
		else
			philo[i].second_fork = &philo[i + 1].fork;
		i++;
	}
}

long	time_calcul(void)
{
	struct timeval	time_calcul;

	gettimeofday(&time_calcul, NULL);
	return ((time_calcul.tv_sec * 1000) + (time_calcul.tv_usec / 1000));
}

void	philos_routine(t_philos *philos)
{
	display_message("HE IS THINKING", philos->philo_id, philos->info);
	pthread_mutex_lock(&philos->fork);
	display_message("FIRST FORK TAKEN", philos->philo_id, philos->info);
	pthread_mutex_lock(philos->second_fork);
	display_message("SECOND FORK TAKEN", philos->philo_id, philos->info);
	philos->has_to_die = time_calcul() + philos->info->die_chrono;
	display_message("HE IS EATING", philos->philo_id, philos->info);
	usleep(philos->info->eat_chrono * 100);
	pthread_mutex_unlock(&philos->fork);
	pthread_mutex_unlock(philos->second_fork);
	display_message("HE IS SLEEPING", philos->philo_id, philos->info);
	usleep(philos->info->sleep_chrono * 100);
}

void	*philos_repeat(void *philo)
{ 
	t_philos	*philos;
	int		count;

	philos = (t_philos *)philo;
	count = 0;
	philos->has_to_die = philos->info->start_chrono + philos->info->die_chrono;
	while (philos->info->gotta_eat == 0 || count < philos->info->gotta_eat)
	{
		philos_routine(philos);
		count++;
		usleep(100);
	}
	philos->out = 1;
	return (NULL);
}

