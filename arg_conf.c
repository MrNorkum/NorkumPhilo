#include "philosophers.h"
#include <stdio.h>

static int	is_numeric(char *s)
{
	if (*s == 43)
		s++;
	if (!('0' <= *s && *s <= '9'))
		return (1);
	while (*s)
	{
		if (!('0' <= *s && *s <= '9'))
			return (1);
		s++;
	}
	return (0);
}

static int	nbr_check(char **av)
{
	int	i;

	i = 1;
	while (i < 5)
		if (is_numeric(av[i++]))
			return (1);
	if (!!av[5])
		if (is_numeric(av[5]))
			return (1);
	return (0);
}

static int	my_atoi(const char *s)
{
	int	res;

	res = 0;
	if (!s)
		return (0);
	if (*s == '+')
		s++;
	if (*s == '0' && !*(s + 1))
		return (-1);
	if (*s == 43)
		s++;
	while ('0' <= *s && *s <= '9')
		res = (res * 10) + (*s++ & 15);
	return (res);
}

static int	nbr_conf(char **av, t_program *x)
{
	x->args.num_of_philo = my_atoi(av[1]);
	if (!x->args.num_of_philo || (char)x->args.num_of_philo == -1)
		return (1);
	x->args.time_to_die = my_atoi(av[2]);
	if (!x->args.time_to_die || (char)x->args.time_to_die == -1)
		return (1);
	x->args.time_to_eat = my_atoi(av[3]);
	if (!x->args.time_to_eat || (char)x->args.time_to_eat == -1)
		return (1);
	x->args.time_to_sleep = my_atoi(av[4]);
	if (!x->args.time_to_sleep || (char)x->args.time_to_sleep == -1)
		return (1);
	x->args.eat_limit = my_atoi(av[5]);
	if ((char)x->args.eat_limit == -1)
		return (1);
	return (0);
}

int	arg_conf(int ac, char **av, t_program *x)
{
	if (ac != 5 && ac != 6)
		return (printf(ARG_ERR), 1);
	if (nbr_check(av))
		return (printf(NBR_ERR_1), 1);
	if (nbr_conf(av, x))
		return (printf(NBR_ERR_2), 1);
	if (x->args.num_of_philo > 200)
		return (printf(CPU_ERR), 1);
	return (0);
}
