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

long	time_calcul(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	philos_routine(t_philo *philos)
{
	display_message("HE IS THINKING", philos->philo_id, philos->info);
	pthread_mutex_lock(&philos->fork);
	display_message("FIRST FORK TAKEN", philos->philo_id, philos->info);
	pthread_mutex_lock(philos->second_fork);
	display_message("SECOND FORK TAKEN", philos->philo_id, philos->info);
	philos->has_to_die = time_calcul() + philos->info->die_chrono;
	display_message("HE IS EATING", philos->philo_id, philos->info);
	usleep(philos->info->eat_chrono * 1000);
	pthread_mutex_unlock(&philos->fork);
	pthread_mutex_unlock(philos->second_fork);
	display_message("HE IS SLEEPING", philos->philo_id, philos->info);
	usleep(philos->info->sleep_chrono * 1000);
}

void	*philos_repeat(void *philo)
{ 
	t_philo	*philos;
	int		count;

	philos = (t_philo *)philo;
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

void	philos_connect(t_info *info, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < info->philos_num)
	{
		philo[i].philo_id = i + 1;
		philo[i].info = info;
		if (i == info->philos_num - 1)
			philo[i].second_fork = &philo[0].fork;
		else
			philo[i].second_fork = &philo[i + 1].fork;
		i++;
	}
}

t_philo	*philos_create(t_info *info)
{
	t_philo	*philo;
	int		i;

	i = -1;
	philo = malloc(sizeof(t_philo) * info->philos_num);
	if (!philo)
		return (NULL);
	while (++i < info->philos_num)
		pthread_mutex_init(&philo[i].fork, NULL);
	philos_connect(info, philo);
	info->start_chrono = time_calcul();
	i = -1;
	while (++i < info->philos_num)
	{
		if (pthread_create(&philo[i].thread, NULL, philos_repeat, &philo[i]))
			return (free(philo), NULL);
		usleep(10);
	}
	i = -1;
	while (++i < info->philos_num)
		pthread_detach(philo[i].thread);
	return (philo);
}
