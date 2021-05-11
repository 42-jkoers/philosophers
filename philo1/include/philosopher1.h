#ifndef PHILOSOPHER1_H
# define PHILOSOPHER1_H

# include <stdbool.h>
# include <sys/types.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>

typedef unsigned long t_time_useconds;
typedef unsigned long t_useconds;

typedef enum e_fork
{
	AVAILABLE,
	IN_USE,
}			t_fork;

typedef enum e_status
{
	FAILURE,
	SUCCESS,
}			t_status;


typedef struct s_globals
{
	t_fork			*forks;
	pthread_mutex_t forks_lock;
	pthread_mutex_t print_lock;
	size_t			n;
}		t_globals;

typedef struct s_input
{
	size_t			n;
	t_useconds		time_to_die;
	t_useconds		time_to_eat;
	t_useconds		time_to_sleep;
	long			must_eat_n;
}		t_input;

typedef struct s_ph
{
	size_t			id;
	pthread_t		threadid;
	t_time_useconds	last_meal;

	size_t			left_fork;
	size_t			right_fork;
	t_useconds		time_to_die;
	t_useconds		time_to_eat;
	t_useconds		time_to_sleep;
	long			must_eat_n;

	t_globals		*g;
}		t_ph;

void	*ph_thread(void *philosoper);
t_time_useconds epoch_useconds(void);

#endif
