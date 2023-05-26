/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-mes <hben-mes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 12:54:53 by hben-mes          #+#    #+#             */
/*   Updated: 2023/05/26 15:47:45 by hben-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_info
{
	pthread_mutex_t	type;
	int				eat_chrono;
	int				sleep_chrono;
	int				die_chrono;
	int				gotta_eat;
	int				situation;
	int				has_eaten;
	long			start_chrono;
	int				philos_num;
}					t_info;

typedef struct s_philos
{
	pthread_t		threads;
	pthread_mutex_t	fork;
	pthread_mutex_t	*second_fork;
	int				out;
	int				max_eating;
	long			has_to_die;
	int				philo_id;
	t_info			*info;
}					t_philos;

void				philos_connect(t_info *info, t_philos *philosopher);
long				time_calcul(void);
void				*philos_repeat(void *str);
t_philos			*philos_create(t_info *info);
int					check_input(int ac, char **av, t_info *info);
void				display(char *s, int id, t_info *info);
void				check_health(t_philos *philosopher);
void				check_death(t_philos *philosopher);
int					check_digit(int ac, char **av);
int					ft_atoi(const char *str);

#endif
