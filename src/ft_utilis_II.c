#include "../include/philo.h"

int ft_take_forks(t_data *data, int num_of_philo)
{
    pthread_mutex_lock(&data->mutex_eat[data->philo[num_of_philo].r_fork]);
    pthread_mutex_lock(&data->mutex_eat[data->philo[num_of_philo].l_fork]);
    ft_calc_time(data);
    pthread_mutex_lock(&data->dead_mutex);
    printf("%d %d has taken fork\n", data->time_now - data->old_time, num_of_philo + 1);
    pthread_mutex_unlock(&data->dead_mutex);
    return (0);
}

int ft_philo_eat(t_data *data, int num_of_philo)
{
    ft_calc_time(data);
    pthread_mutex_lock(&data->dead_mutex);
    data->philo[num_of_philo].old_time_eat = data->time_now - data->old_time;
    printf("%d %d is eating\n", data->time_now - data->old_time, num_of_philo + 1);
    pthread_mutex_unlock(&data->dead_mutex);
    ft_usleep(data, data->time_to_eat);
    data->philo[num_of_philo].num_of_times_eat++;
    pthread_mutex_unlock(&data->mutex_eat[data->philo[num_of_philo].l_fork]);
    pthread_mutex_unlock(&data->mutex_eat[data->philo[num_of_philo].r_fork]);
    return (0);
}

int ft_philo_sleep(t_data *data, int num_of_philo)
{
    ft_calc_time(data);;
    pthread_mutex_lock(&data->dead_mutex);
    printf("%d %d is sleeping\n", data->time_now - data->old_time, num_of_philo + 1);
    pthread_mutex_unlock(&data->dead_mutex);
    ft_usleep(data, data->time_to_sleep);
    ft_calc_time(data);
    pthread_mutex_lock(&data->dead_mutex);
    printf("%d %d is thinking\n", data->time_now - data->old_time, num_of_philo + 1);
    pthread_mutex_unlock(&data->dead_mutex);
    return (0);
}

int ft_check_if_all_eat(t_data *data)
{
    int hmpe;
    int a;

    a = -1;
    hmpe = 0;
    if (data->argc == 5)
        return (0);
    while(++a < data->number_of_philosophers)
    {
        if(data->philo[a].num_of_times_eat >= data->number_of_times_each_philosopher_must_eat)
            hmpe++;
    }
    if(hmpe == data->number_of_philosophers)
    {
        data->all_eat = 1;
        return (1);
    }
    return (0);
}

int ft_check_if_dead(t_data *data, int num_of_philo)
{
    if((data->time_now - data->old_time) - data->philo[num_of_philo].old_time_eat >= data->time_to_die)
    {
        printf("%d %d died\n", data->time_now - data->old_time, num_of_philo + 1);   
        return (1);
    }
    return (0);
}

int ft_calc_time(t_data *data)
{
    (void) data;
    struct timeval tv;

    gettimeofday(&tv, NULL);
    data->time_now = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
    return (data->time_now);
}

void ft_usleep(t_data *data, int time)
{
    int old_time;

    old_time = ft_calc_time(data);
    while((ft_calc_time(data) - old_time) < time)
        usleep(100);
}
