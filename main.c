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
	t_data	data;
	t_philo	*philo;

	data.situation = 0;
	data.has_eaten = 0;
	if (check_input(ac, av, &data))
		return (0);
	pthread_mutex_init(&data.print, NULL);
	philo = philos_create(&data);
	if (philo == NULL)
		return (0);
	while (data.situation == 0)
	{
		if (philo->out == 1)
			philo->data->has_eaten++;
		ft_check_health(philo);
	}
	i = -1;
	while (++i < data.philos_num)
		pthread_mutex_destroy(&philo[i].fork);
	pthread_mutex_destroy(&data.print);
	free(philo);
	return (0);
}