#include "philosophers.h"

void	*die(void *tmp_program)
{
	t_program		*x;
	unsigned char	i;

	x = (t_program *)tmp_program;
	while (!check_eat(x))
	{
		i = -1;
		while (++i < x->args.num_of_philo)
		{
			pthread_mutex_lock(&x->mutex.ctrl_m);
			if ((get_time() - x->philo[i].last_eat) > x->args.time_to_die)
			{
				pthread_mutex_lock(&x->die.die_m);
				x->die.is_die = x->philo[i].id;
				x->others.finished = 1;
				pthread_mutex_unlock(&x->die.die_m);
				x->die.die_time = instant_time(x);
				pthread_mutex_unlock(&x->mutex.ctrl_m);
				return ((void *)0);
			}
			pthread_mutex_unlock(&x->mutex.ctrl_m);
		}
		improved_usleep(1);
	}
	return ((void *)0);
}

void	*life(void *tmp_philo)
{
	t_philo	*philo;

	philo = (t_philo *)(tmp_philo);
	if (!(philo->id % 2))
		improved_usleep(5);
	pthread_mutex_lock(&philo->x->die.die_m);
	while (!philo->x->others.finished)
	{
		pthread_mutex_unlock(&philo->x->die.die_m);
		pthread_mutex_lock(&philo->x->mutex.fork_m[philo->l_fork]);
		p_fork(philo, "l_fork");
		pthread_mutex_lock(&philo->x->mutex.fork_m[philo->r_fork]);
		p_fork(philo, "r_fork");
		p_eat(philo);
		pthread_mutex_unlock(&philo->x->mutex.fork_m[philo->l_fork]);
		pthread_mutex_unlock(&philo->x->mutex.fork_m[philo->r_fork]);
		p_sleep(philo);
		p_think(philo);
		pthread_mutex_lock(&philo->x->die.die_m);
	}
	pthread_mutex_unlock(&philo->x->die.die_m);
	return ((void *)0);
}
