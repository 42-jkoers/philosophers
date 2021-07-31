#include "not_libft/include/not_libft.h"
#include "philosopher1.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

bool	init_globals(t_globals *g, t_input input)
{
	size_t	i;

	g->forks = malloc(input.n * sizeof(pthread_mutex_t));
	if (!g->forks)
		return (false);
	g->forks_in_use = malloc(input.n * sizeof(t_fork));
	if (!g->forks_in_use)
		return (false);
	i = 0;
	while (i < input.n)
	{
		pthread_mutex_init(&g->forks[i], NULL);
		g->forks_in_use[i] = AVAILABLE;
		i++;
	}
	if (pthread_mutex_init(&g->lock, NULL))
	{
		free(g->forks);
		return (exit_error("Create mutex lock failed"));
	}
	g->n = input.n;
	g->start_program = epoch_useconds();
	g->casualty = false;
	return (true);
}

int	main_exit(int code, t_globals *g, t_ph *phs)
{
	if (g)
	{
		pthread_mutex_destroy(&g->lock);
		free(g->forks);
	}
	if (phs)
		free(phs);
	return (code);
}

int	main(int argc, const char **argv)
{
	t_globals	g;
	t_ph		*phs;
	t_input		input;

	if (!parse_input(&input, argc, argv))
		return (1);
	if (input.n <= 1)
	{
		usleep_accurate(input.time_to_die);
		printf("%lu 1 has died\n", input.time_to_die / 1000);
		return (0);
	}
	if (!init_globals(&g, input))
		return (main_exit(1, NULL, NULL));
	phs = phs_create(input, &g);
	if (!phs)
		return (main_exit(1, &g, NULL));
	g.phs = phs;
	if (!phs_start(phs, g.n))
		return (main_exit(1, &g, phs));
	if (!phs_await(phs, input.n))
		return (main_exit(1, &g, phs));
	return (main_exit(0, &g, phs));
}
