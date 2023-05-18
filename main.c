/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-mes <hben-mes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:00:19 by hben-mes          #+#    #+#             */
/*   Updated: 2023/05/06 16:00:19 by hben-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int	main(int ac, char **av)
{
	int		i;
	t_info	info;
	t_philo	*philo;

	info.situation = 0;
	info.has_eaten = 0;
	if (check_input(ac, av, &info))
		return (0);
	pthread_mutex_init(&info.type, NULL);
	philo = philos_create(&info);
	if (philo == NULL)
		return (0);
	while (info.situation == 0)
	{
		if (philo->out == 1)
			philo->info->has_eaten++;
		ft_check_health(philo);
	}
	i = -1;
	while (++i < info.philos_num)
		pthread_mutex_destroy(&philo[i].fork);
	pthread_mutex_destroy(&info.type);
	free(philo);
	return (0);
}