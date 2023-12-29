#include "philosophers.h"
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

u_int64_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, (void *)0) == -1)
		return (1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

unsigned int	instant_time(t_program *x)
{
	return (get_time() - x->others.start_time);
}

void	improved_usleep(u_int64_t time)
{
	uint64_t	wake_up;

	wake_up = get_time() + time;
	while (get_time() < wake_up)
		usleep(200);
}

int	check_eat(t_program *x)
{
	unsigned char	i;

	if (x->args.eat_limit)
	{
		i = -1;
		while (++i < x->args.num_of_philo)
		{
			pthread_mutex_lock(&x->mutex.ctrl_2_m);
			if (x->philo[i].num_of_eat >= x->args.eat_limit)
				x->others.ctrl_eat_limit++;
			pthread_mutex_unlock(&x->mutex.ctrl_2_m);
		}
		pthread_mutex_lock(&x->mutex.ctrl_2_m);
		if (x->others.ctrl_eat_limit >= x->args.num_of_philo)
		{
			pthread_mutex_unlock(&x->mutex.ctrl_2_m);
			pthread_mutex_lock(&x->die.die_m);
			x->others.finished = 1;
			pthread_mutex_unlock(&x->die.die_m);
			return (1);
		}
		pthread_mutex_unlock(&x->mutex.ctrl_2_m);
	}
	return (0);
}

int	one_philo(t_program *x)
{
	if (pthread_create(&x->philo[0].thread, (void *)0, life,
			(void *)&x->philo[0]))
		return (printf(MUTEX_CREATE_ERR), destroy(x));
	pthread_detach(x->philo[0].thread);
	printf(FORK, 1, 1, "l_fork");
	improved_usleep(x->args.time_to_die);
	printf(DIE, x->args.time_to_die + 1, 1);
	return (destroy(x) - 1);
}
