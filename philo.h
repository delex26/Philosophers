#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_data
{
    int             nb_philo;
    int             time_sleep;
    int             time_eat;
    int             time_die;
    int             must_eat;
    int             s_time;
    int             status;
    int             ate;
    pthread_mutex_t print;
}    t_data;

typedef struct s_philo
{
    int             id;
    int             eat_max;
    long            should_die;
    int             leave;
    pthread_t       thread;
    pthread_mutex_t  fork;
    pthread_mutex_t *next_fork;
    t_data          *data;
}   t_philo;

int		check_input(int ac, char **av, t_data *data);
void	display_message(char *s, int id, t_data *data);
t_philo	*ft_create_philosophers(t_data *data);
long	ft_current_time(void);
void	display_message(char *s, int id, t_data *data);

#endif
