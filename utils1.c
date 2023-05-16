/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-mes <hben-mes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:38:41 by hben-mes          #+#    #+#             */
/*   Updated: 2023/05/16 17:04:48 by hben-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int	check_input(int ac, char **av, t_data *data)
{
	if (ac != 6 && ac != 5)
		return(printf("CHECK ARGS NUM\n"), 1);
	if (check_digit(ac, av))
		return(printf("CHECK YOUR INPUT\n"), 1);
	data->gotta_eat = 1;
	data->philos_num = ft_atoi(av[1]);
	data->die_chrono = ft_atoi(av[2]);
	data->eat_chrono = ft_atoi(av[3]);
	data->sleep_chrono = ft_atoi(av[4]);
	if (ac == 6)
	{
		data->gotta_eat = ft_atoi(av[5]);
		if (data->gotta_eat < 1)
			return (0);
	}
	if (ac == 5)
		data->gotta_eat = 0;
	if (data->philos_num < 1 || data->die_chrono < 60
		|| data->eat_chrono < 60 || data->sleep_chrono < 60)
		return (1);
	return (0);
}

void	display_message(char *s, int id, t_data *data)
{
	pthread_mutex_lock(&data->print);
	printf("[%ld] %d %s\n", time_calcul() - data->start_chrono, id, s);
	fflush(stdout);
	pthread_mutex_unlock(&data->print);
}

void	ft_check_health(t_philo *philo)
{
	if (philo->data->has_eaten == philo->data->philos_num)
	{
		usleep(2000);
		pthread_mutex_lock(&philo->data->print);
		philo->data->situation = 1;
	}
	if (time_calcul() >= philo->should_die + 5)
	{
		display_message("RIP", philo->id, philo->data);
		pthread_mutex_lock(&philo->data->print);
		philo->data->situation = 1;
	}
}