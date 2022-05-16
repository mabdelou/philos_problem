/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utilis_I.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:37:07 by mabdelou          #+#    #+#             */
/*   Updated: 2022/05/13 18:37:08 by mabdelou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int ft_error(char *error)
{
    printf("%s\n",error);
    return (1);
}

int	ft_isalpha(int a)
{
	char	c;

	c = (unsigned char )a;
	if ((a >= 65 && a <= 90) || (a >= 97 && a <= 122))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

int ft_check_argument_if_correct(char **argv)
{
    int a;
    int b;

    a = 0;
    b = -1;
    while(argv[++a])
    {
        b = -1;
        while(argv[a][++b])
            if(ft_isalpha(argv[a][b]))
                return (ft_error("invalid argumment\n"));
        if(argv[a][0] == 0)
                return (ft_error("invalid argumment\n"));
    }
    return (0);
}

int ft_create_philos(t_data *data)
{
    data->philo = malloc(sizeof(t_philo) * data->number_of_philosophers);
    if(!data->philo)
        return (ft_error("can't alocate in ft_create_philo\n"));
    data->a = -1;
    while(++data->a < data->number_of_philosophers)
    {
        data->philo[data->a].r_fork = 0;
        data->philo[data->a].l_fork = 0;
        data->philo[data->a].old_time_eat = 0;
    }
    return (0);
}

int ft_join_thread(t_data *data)
{
    int a;
    while(data->all_eat == 0)
    {
        pthread_mutex_lock(&data->dead_mutex);
        a = -1;
        while(++a < data->number_of_philosophers)
            if(ft_check_if_dead(data, a))
                return (1);
        if(ft_check_if_all_eat(data))
            return (1);
        pthread_mutex_unlock(&data->dead_mutex);
    }
    return (0);
}
