#include "not_libft/include/not_libft.h"
#include "philosopher1.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

bool	init_globals_destructor(t_globals *g)
{
	if (!g)
		return (false);
	if (g->forks)
		free (g->forks);
	if (g->forks_in_use)
		free(g->forks_in_use);
	return (false);
}

bool	init_globals(t_globals *g, t_input input)
{
	size_t	i;

	ft_bzero(g, sizeof(t_globals));
	g->forks = malloc(input.n * sizeof(pthread_mutex_t));
	if (!g->forks)
		return (init_globals_destructor(g));
	g->forks_in_use = malloc(input.n * sizeof(t_fork));
	if (!g->forks_in_use)
		return (init_globals_destructor(g));
	i = 0;
	while (i < input.n)
	{
		g->forks_in_use[i] = AVAILABLE;
		if (pthread_mutex_init(&g->forks[i], NULL))
			return (init_globals_destructor(g));
		i++;
	}
	if (pthread_mutex_init(&g->lock, NULL))
		return (init_globals_destructor(g));
	g->n = input.n;
	g->casualty = false;
	g->start_program = epoch_useconds();
	return (true);
}

int	main_destructor(int code, t_globals *g, t_ph *phs)
{
	size_t	i;

	if (g)
	{
		i = 0;
		while (i < g->n)
		{
			pthread_mutex_destroy(&g->forks[i]);
			i++;
		}
		pthread_mutex_destroy(&g->lock);
		free(g->forks);
		free(g->forks_in_use);
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
		return (1);
	phs = phs_create(input, &g);
	if (!phs)
		return (main_destructor(1, &g, NULL));
	g.phs = phs;
	if (!phs_start(phs, g.n))
		return (main_destructor(1, &g, phs));
	if (!phs_await(phs, input.n))
		return (main_destructor(1, &g, phs));
	return (main_destructor(0, &g, phs));
}
