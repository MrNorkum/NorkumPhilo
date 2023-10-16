#include "philosophers.h"
#include <stdio.h>

void	p_fork(t_philo *philo, char *fork)
{
	pthread_mutex_lock(&philo->x->mutex.ctrl_m);
	pthread_mutex_lock(&philo->x->die.die_m);
	if (!philo->x->die.is_die)
	{
		pthread_mutex_unlock(&philo->x->die.die_m);
		pthread_mutex_unlock(&philo->x->mutex.ctrl_m);
		pthread_mutex_lock(&philo->x->mutex.print_m);
		printf(FORK, instant_time(philo->x), philo->id, fork);
		pthread_mutex_unlock(&philo->x->mutex.print_m);
		return ;
	}
	pthread_mutex_unlock(&philo->x->die.die_m);
	pthread_mutex_unlock(&philo->x->mutex.ctrl_m);
}

void	p_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->x->mutex.ctrl_m);
	pthread_mutex_lock(&philo->x->die.die_m);
	if (!philo->x->die.is_die)
	{
		pthread_mutex_unlock(&philo->x->die.die_m);
		pthread_mutex_unlock(&philo->x->mutex.ctrl_m);
		pthread_mutex_lock(&philo->x->mutex.print_m);
		printf(EAT, instant_time(philo->x), philo->id);
		pthread_mutex_unlock(&philo->x->mutex.print_m);
		improved_usleep(philo->x->args.time_to_eat);
		pthread_mutex_lock(&philo->x->mutex.ctrl_m);
		philo->last_eat = get_time();
		pthread_mutex_unlock(&philo->x->mutex.ctrl_m);
		pthread_mutex_lock(&philo->x->mutex.ctrl_2_m);
		philo->num_of_eat++;
		pthread_mutex_unlock(&philo->x->mutex.ctrl_2_m);
		return ;
	}
	pthread_mutex_unlock(&philo->x->die.die_m);
	pthread_mutex_unlock(&philo->x->mutex.ctrl_m);
}

void	p_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->x->mutex.ctrl_m);
	pthread_mutex_lock(&philo->x->die.die_m);
	if (!philo->x->die.is_die)
	{
		pthread_mutex_unlock(&philo->x->die.die_m);
		pthread_mutex_unlock(&philo->x->mutex.ctrl_m);
		pthread_mutex_lock(&philo->x->mutex.print_m);
		printf(SLEEP, instant_time(philo->x), philo->id);
		pthread_mutex_unlock(&philo->x->mutex.print_m);
		improved_usleep(philo->x->args.time_to_sleep);
		return ;
	}
	pthread_mutex_unlock(&philo->x->die.die_m);
	pthread_mutex_unlock(&philo->x->mutex.ctrl_m);
}

void	p_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->x->mutex.ctrl_m);
	pthread_mutex_lock(&philo->x->die.die_m);
	if (!philo->x->die.is_die)
	{
		pthread_mutex_unlock(&philo->x->die.die_m);
		pthread_mutex_unlock(&philo->x->mutex.ctrl_m);
		pthread_mutex_lock(&philo->x->mutex.print_m);
		printf(THINK, instant_time(philo->x), philo->id);
		pthread_mutex_unlock(&philo->x->mutex.print_m);
		return ;
	}
	pthread_mutex_unlock(&philo->x->die.die_m);
	pthread_mutex_unlock(&philo->x->mutex.ctrl_m);
}
