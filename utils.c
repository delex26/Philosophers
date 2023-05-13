/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-mes <hben-mes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:00:00 by hben-mes          #+#    #+#             */
/*   Updated: 2023/05/06 16:00:00 by hben-mes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}


int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int check_digit(int ac, char **av) 
{
    int i = 1;
    int j = 0;

    while (i < ac) 
	{
        while (av[i][j] != '\0') 
		{
            if (!ft_isdigit(av[i][j]) && av[i][j] != '+') 
			{
                return (1);  
            }
            j++;
        }
        i++;
        j = 0;
    }

    return (0); 
}

int	ft_atoi(const char *str)
{
	int	i;
	int	n;
	int	res;

	i = 0;
	res = 0;
	n = 1;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-')
	{
		n = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (n * res);
}
