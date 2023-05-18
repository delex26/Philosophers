/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-mes <hben-mes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:38:41 by hben-mes          #+#    #+#             */
/*   Updated: 2023/05/18 20:16:34 by hben-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int	check_input(int ac, char **av, t_info *info)
{
	if (ac != 6 && ac != 5)
		return(printf("CHECK ARGS NUM\n"), 1);
	if (check_digit(ac, av))
		return(printf("CHECK YOUR INPUT\n"), 1);
	info->gotta_eat = 1;
	info->philos_num = ft_atoi(av[1]);
	info->die_chrono = ft_atoi(av[2]);
	info->eat_chrono = ft_atoi(av[3]);
	info->sleep_chrono = ft_atoi(av[4]);
	if (ac == 6)
	{
		info->gotta_eat = ft_atoi(av[5]);
		if (info->gotta_eat < 1)
			return (0);
	}
	if (ac == 5)
		info->gotta_eat = 0;
	if (info->philos_num < 1 || info->die_chrono < 60
		|| info->eat_chrono < 60 || info->sleep_chrono < 60)
		return (1);
	return (0);
}

void	display_message(char *s, int id, t_info *info)
{
	pthread_mutex_lock(&info->type);
	printf("[%ld] %d %s\n", time_calcul() - info->start_chrono, id, s);
	fflush(stdout);
	pthread_mutex_unlock(&info->type);
}

void	ft_check_health(t_philo *philo)
{
	if (philo->info->has_eaten == philo->info->philos_num)
	{
		usleep(2000);
		pthread_mutex_lock(&philo->info->type);
		philo->info->situation = 1;
	}
	if (time_calcul() >= philo->has_to_die + 5)
	{
		display_message("RIP", philo->philo_id, philo->info);
		pthread_mutex_lock(&philo->info->type);
		philo->info->situation = 1;
	}
}