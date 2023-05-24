/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-mes <hben-mes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:00:19 by hben-mes          #+#    #+#             */
/*   Updated: 2023/05/24 22:33:42 by hben-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philos	*philos_create(t_info *info)
{
	t_philos	*philosopher;
	int			i;

	i = -1;
	philosopher = malloc(sizeof(t_philos) * info->philos_num);
	info->start_chrono = time_calcul();
	if (!philosopher)
		return (NULL);
	while (++i < info->philos_num)
		pthread_mutex_init(&philosopher[i].fork, NULL);
	philos_connect(info, philosopher);
	i = -1;
	while (++i < info->philos_num)
	{
		if (pthread_create(&philosopher[i].threads, NULL, philos_repeat,
				&philosopher[i]))
			return (free(philosopher), NULL);
		usleep(10);
	}
	i = -1;
	while (++i < info->philos_num)
		pthread_detach(philosopher[i].threads);
	return (philosopher);
}

int	main(int ac, char **av)
{
	t_philos	*philosopher;
	t_info		info;
	int			i;

	i = -1;
	if (check_input(ac, av, &info))
		return (0);
	pthread_mutex_init(&info.type, NULL);
	philosopher = philos_create(&info);
	if (philosopher == NULL)
		return (0);
	info.has_eaten = 0;
	info.situation = 0;
	while (info.situation == 0)
	{
		if (philosopher->out == 1)
			philosopher->info->has_eaten++;
		check_philos(philosopher);
		check_death(philosopher);
	}
	while (++i < info.philos_num)
		pthread_mutex_destroy(&philosopher[i].fork);
	pthread_mutex_destroy(&info.type);
	free(philosopher);
	return (0);
}
