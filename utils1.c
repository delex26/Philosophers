/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-mes <hben-mes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:38:41 by hben-mes          #+#    #+#             */
/*   Updated: 2023/05/24 20:00:27 by hben-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int	check_input(int ac, char **av, t_info *info)
{
	if (check_digit(ac, av))
		return(printf("CHECK YOUR INPUT\n"), 1);
	if (ac != 6 && ac != 5)
		return(printf("CHECK ARGS NUM\n"), 1);
	info->gotta_eat = 1;
	info->philos_num = ft_atoi(av[1]);
	info->die_chrono = ft_atoi(av[2]);
	info->eat_chrono = ft_atoi(av[3]);
	info->sleep_chrono = ft_atoi(av[4]);
	if (ac == 5)
		info->gotta_eat = 0;
	if (ac == 6)
	{
		info->gotta_eat = ft_atoi(av[5]);
		if (info->gotta_eat < 1)
			return (0);
	}
	if (info->philos_num < 1 || info->philos_num > 200 || info->die_chrono < 60
		|| info->eat_chrono < 60 || info->sleep_chrono < 60)
		return (1);
		return (0);
}

void	display_message(char *s, int id, t_info *info)
{
	long int	time_elapsed;

	time_elapsed = time_calcul() - info->start_chrono;
	pthread_mutex_lock(&info->type);
	printf("[%ld] %d %s\n", time_elapsed, id, s);
	pthread_mutex_unlock(&info->type);
}

void	check_philos(t_philos *philosopher)
{
	if (philosopher->info->has_eaten == philosopher->info->philos_num)
	{
		usleep(1000);
		pthread_mutex_lock(&philosopher->info->type);
		philosopher->info->situation = 1;
	}
}

void	check_death(t_philos *philosopher)
{
	if (time_calcul() >= philosopher->has_to_die)
	{
		display_message("RIP", philosopher->philo_id, philosopher->info);
		pthread_mutex_lock(&philosopher->info->type);
		philosopher->info->situation = 1;
	}
}