/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:37:47 by hben-mes          #+#    #+#             */
/*   Updated: 2023/05/14 18:50:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int	check_input(int ac, char **av, t_data *data)
{
	if (ac != 6 && ac != 5)
		return(printf("wrong arguments\n"), 1);
	if (check_digit(ac, av))
		return(printf("check the content of your param\n"), 1);
	data->must_eat = 1;
	data->nb_philo = ft_atoi(av[1]);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]);
	data->time_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		data->must_eat = ft_atoi(av[5]);
		if (data->must_eat < 1)
			return (0);
	}
	if (ac == 5)
		data->must_eat = 0;
	if (data->nb_philo < 1 || data->time_die < 60
		|| data->time_eat < 60 || data->time_sleep < 60)
		return (1);
	return (0);
}

void	display_message(char *s, int id, t_data *data)
{
	pthread_mutex_lock(&data->print);
	printf("[%ld] %d %s\n", ft_current_time() - data->s_time, id, s);
	fflush(stdout);
	pthread_mutex_unlock(&data->print);
}

void	ft_check_health(t_philo *philo)
{
	if (philo->data->ate == philo->data->nb_philo)
	{
		usleep(2000);
		pthread_mutex_lock(&philo->data->print);
		philo->data->status = 1;
	}
	if (ft_current_time() >= philo->should_die + 5)
	{
		display_message("died", philo->id, philo->data);
		pthread_mutex_lock(&philo->data->print);
		philo->data->status = 1;
	}
}