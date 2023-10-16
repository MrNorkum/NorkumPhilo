#include "philosophers.h"

int	main(int ac, char **av)
{
	t_program	x;

	if (arg_conf(ac, av, &x))
		return (1);
	return (general_conf(&x));
}
