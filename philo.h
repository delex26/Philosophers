/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-mes <hben-mes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 12:54:53 by hben-mes          #+#    #+#             */
/*   Updated: 2023/05/13 12:54:53 by hben-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include   <unistd.h>
# include   <stdlib.h>
# include   <sys/time.h>
# include   <pthread.h>
# include   <stdio.h>

typedef struct s_info
{
	int				eat_chrono;
	int				sleep_chrono;
	int				die_chrono;
	int				gotta_eat;
	int				situation;
	int				has_eaten;
	long			start_chrono;
	int				philos_num;
	pthread_mutex_t	type;
}	t_info;

typedef struct s_philo
{
	int				out;
	int				max_eating;
	long			has_to_die;
	int				philo_id;
	pthread_t		thread;
	pthread_mutex_t	fork;
	pthread_mutex_t	*second_fork;
	t_info			*info;
}	t_philo;

long	time_calcul(void);
t_philo	*philos_create(t_info *info);
int		check_input(int ac, char **av, t_info *info);
void	display_message(char *s, int id, t_info *info);
void	ft_check_health(t_philo *philo);
int		ft_isdigit(int c);
int		check_digit(int ac, char **av);
int		ft_atoi(const char *str);


#endif 

