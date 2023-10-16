#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdint.h>

# define ARG_ERR "Number of arguments is wrong\n"
# define NBR_ERR_1 "Arguments must be a counting number\n"
# define NBR_ERR_2 "Arguments must be non-zero\n"
# define CPU_ERR "CPU Melted ?!\n"
# define FORK_CREATE_ERR "Failed to create forks\n"
# define PHILO_CREATE_ERR "Philosophers could not be created\n"
# define MUTEX_INIT_ERR "Mutex failed to initialize\n"
# define MUTEX_CREATE_ERR "Could not create mutex\n"
# define FORK "\033[0;34m%d| \033[0;33m%d. \033[0;36mphilo took the fork (%s)\n"
# define EAT "\033[0;34m%d| \033[0;33m%d. \033[0;32mphilo is eating\033[0m\n"
# define SLEEP "\033[0;34m%d| \033[0;33m%d. \033[0;35mphilo sleeping\033[0m\n"
# define THINK "\033[0;34m%d| \033[0;33m%d. \033[0;37mphilo thinking\033[0m\n"
# define DIE "\033[0;34m%d| \033[0;33m%d. \033[0;31mphilo died :(\033[0m\n"

typedef struct s_args
{
	unsigned char		num_of_philo;
	unsigned int		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	unsigned char		eat_limit;
}						t_args;

typedef struct s_mutex
{
	pthread_mutex_t		print_m;
	pthread_mutex_t		ctrl_m;
	pthread_mutex_t		ctrl_2_m;
	pthread_mutex_t		*fork_m;
}						t_mutex;

typedef struct s_philo
{
	pthread_t			thread;
	unsigned char		id;
	unsigned char		l_fork;
	unsigned char		r_fork;
	uint64_t			last_eat;
	unsigned char		num_of_eat;
	struct s_program	*x;
}						t_philo;

typedef struct s_die
{
	pthread_t			die_t;
	pthread_mutex_t		die_m;
	unsigned char		is_die;
	unsigned int		die_time;
}						t_die;

typedef struct s_others
{
	uint64_t			start_time;
	unsigned char		ctrl_eat_limit;
	unsigned char		finished;
}						t_others;

typedef struct s_program
{
	t_args				args;
	t_philo				*philo;
	t_mutex				mutex;
	t_die				die;
	t_others			others;
}						t_program;

int						free_malloc(t_program *x);
int						init_error_fork(t_program *x, int idx);
int						destroy(t_program *x);
int						create_error_fork(t_program *x, int idx);
int						finish_destroy(t_program *x);
u_int64_t				get_time(void);
unsigned int			instant_time(t_program *x);
void					improved_usleep(u_int64_t time);
void					p_fork(t_philo *philo, char *fork);
void					p_eat(t_philo *philo);
void					p_sleep(t_philo *philo);
void					p_think(t_philo *philo);
int						check_eat(t_program *x);
void					*die(void *tmp_program);
void					*life(void *tmp_philo);
int						arg_conf(int ac, char **av, t_program *x);
int						one_philo(t_program *x);
int						general_conf(t_program *x);

#endif
