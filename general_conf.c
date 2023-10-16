#include "philosophers.h"
#include <stdio.h>
#include <stdlib.h>

static int	allocate(t_program *x)
{
	x->mutex.fork_m = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* x->args.num_of_philo);
	if (!x->mutex.fork_m)
		return (printf(FORK_CREATE_ERR), 1);
	x->philo = (t_philo *)malloc(sizeof(t_philo) * x->args.num_of_philo);
	if (!x->philo)
		return (printf(PHILO_CREATE_ERR), free(x->mutex.fork_m), 1);
	return (0);
}

static int	basic_initialize(t_program *x)
{
	if (pthread_mutex_init(&x->mutex.print_m, (void *)0))
		return (printf(MUTEX_INIT_ERR), free_malloc(x));
	if (pthread_mutex_init(&x->mutex.ctrl_m, (void *)0))
	{
		pthread_mutex_destroy(&x->mutex.print_m);
		return (printf(MUTEX_INIT_ERR), free_malloc(x));
	}
	if (pthread_mutex_init(&x->mutex.ctrl_2_m, (void *)0))
	{
		pthread_mutex_destroy(&x->mutex.print_m);
		pthread_mutex_destroy(&x->mutex.ctrl_m);
		return (printf(MUTEX_INIT_ERR), free_malloc(x));
	}
	if (pthread_mutex_init(&x->die.die_m, (void *)0))
	{
		pthread_mutex_destroy(&x->mutex.print_m);
		pthread_mutex_destroy(&x->mutex.ctrl_m);
		pthread_mutex_destroy(&x->mutex.ctrl_2_m);
		return (printf(MUTEX_INIT_ERR), free_malloc(x));
	}
	return (0);
}

static int	initialize(t_program *x)
{
	int	i;

	i = -1;
	if (basic_initialize(x))
		return (1);
	while (++i < x->args.num_of_philo)
	{
		x->philo[i].id = i + 1;
		x->philo[i].l_fork = i;
		if (!i)
			x->philo[i].r_fork = x->args.num_of_philo - 1;
		else
			x->philo[i].r_fork = i - 1;
		x->philo[i].num_of_eat = 0;
		x->philo[i].last_eat = get_time();
		x->philo[i].x = x;
		if (pthread_mutex_init(&x->mutex.fork_m[i], (void *)0))
			return (printf(MUTEX_INIT_ERR), init_error_fork(x, i));
	}
	return (0);
}

static int	creation(t_program *x)
{
	unsigned char	i;

	i = -1;
	x->die.is_die = 0;
	x->others.ctrl_eat_limit = 0;
	x->others.finished = 0;
	x->others.start_time = get_time();
	while (++i < x->args.num_of_philo)
	{
		if (pthread_create(&x->philo[i].thread, (void *)0, life,
				(void *)&x->philo[i]))
			return (create_error_fork(x, i));
	}
	if (pthread_create(&x->die.die_t, (void *)0, die, (void *)x))
		return (printf(MUTEX_CREATE_ERR), destroy(x));
	return (finish_destroy(x));
}

int	general_conf(t_program *x)
{
	if (allocate(x))
		return (1);
	if (initialize(x))
		return (1);
	if (x->args.num_of_philo == 1)
		return (one_philo(x));
	return (creation(x));
}
