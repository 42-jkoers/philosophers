#include "philosopher1.h"

static void	create_ph(t_ph *ph, size_t id, t_input input, t_globals *g)
{
	ph->id = id;
	ph->last_meal = epoch_useconds();
	if (ph->id == 0)
		ph->left_fork = input.n - 1;
	else
		ph->left_fork = ph->id - 1;
	ph->right_fork = (ph->id + 1) % input.n;
	ph->time_to_die = input.time_to_die;
	ph->time_to_eat = input.time_to_eat;
	ph->time_to_sleep = input.time_to_sleep;
	ph->must_eat_n = input.must_eat_n;
	ph->g = g;
}

t_ph	*phs_create(t_input input, t_globals *g)
{
	t_ph		*phs;
	size_t		i;

	phs = malloc(input.n * sizeof(t_ph));
	i = 0;
	while (i < input.n)
	{
		create_ph(&phs[i], i, input, g);
		i++;
	}
	return (phs);
}

bool	phs_await(t_ph *phs, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (pthread_join(phs[i].threadid, NULL))
			return (exit_error("Thread join failed"));
		i++;
	}
	return (true);
}

bool phs_start(t_ph *phs, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (pthread_create(&phs[i].threadid, NULL, &ph_thread, (void *)(&phs[i])))
			return (exit_error("Thread join failed"));
		i++;
	}
	return (true);
}
